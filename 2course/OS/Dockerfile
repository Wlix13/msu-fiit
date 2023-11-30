FROM --platform=amd64 ubuntu:lunar

RUN apt-get update && \
    apt-get install -y valgrind gcc make tmux && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

RUN echo "alias valgrind='valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all'" >> ~/.bashrc

WORKDIR /app

ENTRYPOINT ["/bin/bash"]