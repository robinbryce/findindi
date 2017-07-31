#!/bin/bash
scriptdir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

apt-get install -y \
    libc++-helpers \
    iwyu \
    libclang-4.0-dev \
    undertaker \
    clang-4.0 \
    libclang-common-4.0-dev \
    libclang1-4.0 \
    lldb-4.0 \
    gdbserver \
    clang-4.0-doc \
    clang-4.0-examples \
    clang-format-4.0 \
    clang-tidy-4.0 \
    libclang-4.0-dev \
    libclang1-4.0-dbg \
    python-clang-4.0 \
    python-lldb-4.0 \
    cmake
