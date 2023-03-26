FROM ubuntu:lunar
ENV DEBIAN_FRONTEND noninteractive
ENV TZ=Europe/Moscow


RUN apt update && \
    apt install gcc fpc vim -y && \
    rm -rf /var/lib/apt/lists/*

COPY ./build_pas.sh /usr/bin/build
RUN chmod +x /usr/bin/build

WORKDIR /data