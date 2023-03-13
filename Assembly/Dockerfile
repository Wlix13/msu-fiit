FROM ubuntu:23.04
ENV DEBIAN_FRONTEND noninteractive

RUN apt update && \
    apt install gcc gcc-multilib mono-mcs nasm -y && \
    rm -rf /var/lib/apt/lists/*

COPY ./build_asm.sh /usr/bin/build_asm
COPY ./io32.inc /usr/lib/gcc/io.inc
RUN chmod +x /usr/bin/build_asm

WORKDIR /data