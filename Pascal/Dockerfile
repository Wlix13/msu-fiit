FROM ubuntu:23.04
ENV DEBIAN_FRONTEND noninteractive

RUN apt update && \
    apt install gcc fpc -y && \
    rm -rf /var/lib/apt/lists/*

COPY ./build_pas.sh /usr/bin/build_pas
RUN chmod +x /usr/bin/build_pas

WORKDIR /data