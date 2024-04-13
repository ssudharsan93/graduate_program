
#!/usr/local/bin/python3

import os
from newsapi import NewsApiClient
from datetime import datetime, timedelta
import time
from kafka import KafkaProducer

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
            exclude_domains='techcrunch.com',
            language='en',
            sort_by='relevancy',
#            from_param=start_date,
#            to=curr_inter_date,
            page=2
        )

        time.sleep(trigger_interval)

        for article in all_articles['articles']:
            for prop_key, prop_val in article.items():
                producer.send('topic1', key=prop_key, value=prop_val.encode('utf-8'))
