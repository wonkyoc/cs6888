#!/bin/bash

REDIS=redis-6.2.6.tar.gz

setup() {
    if [[ ! -e $REDIS ]]; then
        wget https://download.redis.io/releases/redis-6.2.6.tar.gz
        cp $REDIS klee/
    fi
    cd klee
    docker build .
}

setup
