
#!/usr/local/bin/python3

import os
from newsapi import NewsApiClient
from datetime import datetime, timedelta
import time
from kafka import KafkaProducer
from langdetect import detect

min_intervals = [15, 30, 45, 60]
day_intervals = [7, 14, 21, 28]
start_date = datetime.strptime('2024-03-12', '%Y-%m-%d')
dates = [(start_date + timedelta(days=delta)).strftime('%Y-%m-%d') for delta in range(32)]
trigger_interval = 5

if __name__ == "__main__":
    newsapi = NewsApiClient(api_key=os.environ["NEWS_API_KEY"])
    producer = KafkaProducer(bootstrap_servers='localhost:9092')

    while (True):
        curr_inter_date = datetime.now()
        all_articles = newsapi.get_everything(
            q='ukraine',
            language='en',
            sort_by='relevancy',
#            from_param=start_date,
#            to=curr_inter_date,
            page=1
        )

        time.sleep(trigger_interval)

        for article in all_articles['articles']:
            if ( ( article.get('content', None) ) ) :
                if ( detect(article['content']) == 'en' ):
                    producer.send(
                        'topic1',
                        key='content'.encode('utf-8'),
                        value=article['content'].encode('utf-8')
                    )

