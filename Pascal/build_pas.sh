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

fpc -O1 -gh $name.pas
if [ $? -ne 0 ]; then
    exit
fi
rm $name.o

echo "Running your code $name.pas:"
./$name
if [ $? -ne 0 ]; then
    exit
fi
