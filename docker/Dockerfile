FROM ubuntu:16.04

LABEL maintainer "Robin Bryce <robinbryce@gmail.com>"

FROM ubuntu:16.04

RUN \
  sed -i 's/# \(.*multiverse$\)/\1/g' /etc/apt/sources.list && \
  apt-get update && \
  apt-get -y upgrade && \
  apt-get install -y build-essential && \
  apt-get install -y software-properties-common && \
  apt-get install -y byobu curl git htop man unzip vim wget

# Started with
# apt-cache search clang | grep -vE "3.[0-9]"

RUN  apt-get install -y \
    libc++-helpers \
    iwyu \
    libclang-dev \
    undertaker \
    clang-4.0 \
    libclang-common-4.0-dev \
    libclang1-4.0 \
    lldb-4.0 \
    clang-4.0-doc \
    clang-4.0-examples \
    clang-format-4.0 \
    clang-tidy-4.0 \
    libclang-4.0-dev \
    libclang1-4.0-dbg \
    python-clang-4.0 \
    python-lldb-4.0 \
    cmake && \
    ln -s /usr/bin/clang-4.0 /usr/bin/clang && \
    ln -s /usr/bin/clang++-4.0 /usr/bin/clang++ && \
    ln -s /usr/bin/lldb-server-4.0 /usr/bin/lldb-server

# For lldb-server
EXPOSE 3000
