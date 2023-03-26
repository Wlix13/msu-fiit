FROM ubuntu:lunar
ENV DEBIAN_FRONTEND noninteractive
ENV TZ=Europe/Moscow

RUN apt update && \
    apt install gcc gcc-multilib vim nasm -y && \
    rm -rf /var/lib/apt/lists/*

COPY ./build_asm.sh /usr/bin/build_asm
COPY ./io32.inc /usr/lib/gcc/io.inc
COPY ./io64.inc /usr/lib/gcc/io64.inc
RUN chmod +x /usr/bin/build_asm