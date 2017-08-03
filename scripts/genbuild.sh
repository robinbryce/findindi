#!/bin/bash
scriptdir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $scriptdir/../workspace
rm -rf build && mkdir build
cd build
cmake \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    -DCMAKE_C_COMPILER=/usr/bin/clang \
    -DCMAKE_CXX_COMPILER=/usr/bin/clang++ \
    -DCMAKE_BUILD_TYPE=Debug \
    $scriptdir/../src
