#
# Licensed to the Apache Software Foundation (ASF) under one or more
# contributor license agreements.  See the NOTICE file distributed with
# this work for additional information regarding copyright ownership.
# The ASF licenses this file to You under the Apache License, Version 2.0
# (the "License"); you may not use this file except in compliance with
# the License.  You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

"""
 Consumes messages from one or more topics in Kafka and does wordcount.
 Usage: structured_kafka_wordcount.py <bootstrap-servers> <subscribe-type> <topics>
   <bootstrap-servers> The Kafka "bootstrap.servers" configuration. A
   comma-separated list of host:port.
   <subscribe-type> There are three kinds of type, i.e. 'assign', 'subscribe',
   'subscribePattern'.
   |- <assign> Specific TopicPartitions to consume. Json string
   |  {"topicA":[0,1],"topicB":[2,4]}.
   |- <subscribe> The topic list to subscribe. A comma-separated list of
   |  topics.
   |- <subscribePattern> The pattern used to subscribe to topic(s).
   |  Java regex string.
   |- Only one of "assign, "subscribe" or "subscribePattern" options can be
   |  specified for Kafka source.
   <topics> Different value format depends on the value of 'subscribe-type'.

 Run the example
    `$ bin/spark-submit examples/src/main/python/sql/streaming/structured_kafka_wordcount.py \
    host1:port1,host2:port2 subscribe topic1,topic2`
"""
from __future__ import print_function

import sys

from pyspark.sql import SparkSession
from pyspark.sql.functions import udf, col, size, desc, \
                                  concat, lit, explode, split
from pyspark.sql.types import ArrayType, StringType
import spacy
import nltk
nltk.download('punkt')
nltk.download('stopwords')
from nltk.tokenize import word_tokenize
from nltk.corpus import stopwords
import os

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("""
        Usage: structured_kafka_wordcount.py <bootstrap-servers> <subscribe-type> <topics>
        """, file=sys.stderr)
        sys.exit(-1)

    bootstrapServers = sys.argv[1]
    subscribeType = sys.argv[2]
    topics = sys.argv[3]
    ner_tagger = spacy.load("en_core_web_sm")
    en_stopwords = set(stopwords.words('english'))

    spark = SparkSession\
        .builder\
        .appName("Assignment3")\
        .getOrCreate()

    spark.sparkContext.setLogLevel("ERROR")

    # Create DataSet representing the stream of input lines from kafka
    articles = spark\
        .readStream\
        .format("kafka")\
        .option("kafka.bootstrap.servers", bootstrapServers)\
        .option(subscribeType, "topic1")\
        .load()\
        .selectExpr("CAST(key AS STRING)", "CAST(value AS STRING)")

    def get_named_entities(text):
        tokens = word_tokenize(text.lower())
        tokens = list(filter(lambda x: x not in en_stopwords, tokens))
        tokens = list(filter(lambda x: x.isalpha(), tokens))
        tokens = list(filter(lambda x: x not in ["li", "getty", "images"] , tokens)) #li token keeps appearing
        text = " ".join(tokens)
        doc = ner_tagger(text)
        entities = [ 
            ent.text for ent in doc.ents 
            if ent.label_ in [
                "PERSON", "ORG", "LOC", "PRODUCT", "EVENT", "WORK_OF_ART"
            ]
        ]

        flattened_entities = list()

        for entity in entities:
            if " " in entity: flattened_entities += entity.split(" ")
            else: flattened_entities + [ entity ]

        return flattened_entities

    named_entities_udf = udf(get_named_entities, ArrayType(StringType()))
    articles = articles.withColumn("entities", named_entities_udf(col("value")))
    # drop rows with no named entities
    articles = articles.filter(size(col("entities")) > 0)
    articles = articles.select(
        "entities", 
        explode("entities").alias("entity")
    ).drop("entities")

    word_counts = articles.groupBy('entity') \
        .count() \
        .orderBy(desc('count'))
        .withColumnRenamed('entity', 'word')

    #query = result\
    #    .writeStream\
    #    .outputMode('complete')\
    #    .format('console')\
    #    .start()

    #query.awaitTermination()


    # Start running the query that prints the running counts to the other kafka topic
    checkpoint_dir = os.path.join(os.getcwd(), 'checkpoint')
    if not os.path.exists(checkpoint_dir):
        os.mkdir(checkpoint_dir)

    query = word_counts.selectExpr("to_json(struct(*)) AS value") \
        .writeStream \
        .format("kafka") \
        .option("kafka.bootstrap.servers", bootstrapServers) \
        .option("topic", "topic2") \
        .outputMode('complete') \
        .option("checkpointLocation", checkpoint_dir) \
        .start()

    query.awaitTermination()
