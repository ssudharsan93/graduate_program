#!/bin/bash

# Function to run a process in the background and save its PID to a file
run_processes() {
    eval $1 $2 > $3 &
    echo $1
    echo $2
    echo $3
}

# Function to kill all processes using their PIDs from the file
kill_processes() {
    process_keywords=('zookeeper' 'kafka' 'assignment3_producer')
    for element in "${process_keywords[@]}"; do
        echo "Killing $element..."
        kill -9 `ps -ef | grep $element | awk '{print $2}' | head -1`
    done

    exit 1
}


zookeeper_cmd="$KAFKA_HOME/bin/zookeeper-server-start.sh $KAFKA_HOME/config/zookeeper.properties zookeeper.log"
kafka_cmd="$KAFKA_HOME/bin/kafka-server-start.sh $KAFKA_HOME/config/server.properties kafka.log"
create_topic1_cmd="$KAFKA_HOME/bin/kafka-topics.sh --create --topic topic1 --bootstrap-server localhost:9092"
create_topic2_cmd="$KAFKA_HOME/bin/kafka-topics.sh --create --topic topic2 --bootstrap-server localhost:9092"
python_producer_cmd="/usr/local/bin/python3.11 assignment3_producer.py producer.log"

run_processes $zookeeper_cmd
sleep 5
run_processes $kafka_cmd
sleep 5

$create_topic1_cmd
$create_topic2_cmd

run_processes $python_producer_cmd
sleep 5

trap kill_processes SIGINT

while true; do
    sleep 50
done