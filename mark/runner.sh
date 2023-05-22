#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Usage: $0 <ip_address> <port>"
    exit 1
fi

ip_address=$1
port=$2

# Start the server
./bin/server $port &

# Wait for the server to start listening
sleep 2

# Run 100 instances of the client program
for ((i=1; i<=100; i++))
do
    ./bin/client $ip_address $port &
done

# Wait for all clients to finish
wait

# Kill the server
killall server
