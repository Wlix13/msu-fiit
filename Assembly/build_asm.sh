#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: build_asm.sh <asm-file-name>"
    exit
fi

name=${1%.*}

if [ $name = $1 ]; then
    echo "You must use file extension"
    exit
fi

osname=$(uname -s)
if [ $? -ne 0 ]; then
    exit
fi

c_temp=/tmp/_asm_build_$$.c
o_temp=/tmp/_asm_build_$$.o

if [ $? -ne 0 ]; then
    exit
fi

# Determine the system type
case $(echo $osname | tr [:upper:] [:lower:]) in
*cygwin*)
    systype=CYGWIN
    objformat=win32
    ;;
*linux* | *freebsd*)
    systype=UNIX
    objformat=elf32
    ;;
*darwin*)
    systype=DARWIN
    objformat=macho32
    ;;
*)
    echo "Not supported OS: $osname"
    exit 1
    ;;
esac

# Compile the C file for io.inc
echo '#include <stdio.h>' >> $c_temp
echo 'FILE *get_stdin(void) { return stdin; }' >> $c_temp
echo 'FILE *get_stdout(void) { return stdout; }' >> $c_temp
gcc -c -x c -m32 -g $c_temp -o $o_temp 

if [ ! -d "/data/build" ]; then
    mkdir /data/build
fi

# Compile the assembly file
nasm -W+all -g -i/usr/lib/gcc/ -f $objformat -D$systype $1 -o /data/build/$name.o
if [ $? -ne 0 ]; then
    rm -f $c_temp $o_temp /data/build/$name.o
    exit
fi

# Link the object files
gcc /data/build/$name.o $o_temp -g -o /data/build/$name -m32
rm -f $c_temp $o_temp /data/build/$name.o

if [ $? -ne 0 ]; then
    exit
fi

# Run the program
echo -e "\nRunning $name:\n"
/data/build/$name
