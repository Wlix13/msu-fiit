FROM --platform=linux/x86_64 ubuntu:lunar
ENV DEBIAN_FRONTEND noninteractive \
    TZ=Europe/Moscow

RUN apt update && \
    apt install gcc gcc-multilib vim nasm build-essential -y && \
    rm -rf /var/lib/apt/lists/*

COPY ./build_asm.sh /usr/bin/build
RUN chmod +x /usr/bin/build

COPY ./io32.inc /usr/lib/gcc/io.inc
COPY ./io64.inc /usr/lib/gcc/io64.inc

WORKDIR /data