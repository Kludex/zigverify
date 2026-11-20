FROM ubuntu:24.04
RUN apt-get update -qq && apt-get install -y -qq --no-install-recommends cbmc gcc libc6-dev && rm -rf /var/lib/apt/lists/*
