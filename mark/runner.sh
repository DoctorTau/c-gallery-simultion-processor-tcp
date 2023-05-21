#!/bin/bash

# Start the server
./server &

# Wait for the server to start listening
sleep 2

# Run 100 instances of the client program
for ((i=1; i<=100; i++))
do
    ./client &
done

# Wait for all clients to finish
wait

# Kill the server
killall server
