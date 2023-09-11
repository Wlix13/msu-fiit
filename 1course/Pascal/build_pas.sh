#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: build_pas.sh <pascal-file-name>"
    exit
fi

name=${1%.*}

if [ $name = $1 ]; then
    echo "You must use file extension"
    exit
fi

if [ ! -d "/data/build" ]; then
    mkdir /data/build
fi

# Compile the Pascal file
fpc -O1 -gh $name.pas -o /data/build/$name
if [ $? -ne 0 ]; then
    exit
fi

rm /data/build/$name.o

# Run the program
echo -e "\nRunning $name:\n"
/data/build/$name
