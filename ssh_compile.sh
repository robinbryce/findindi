#!/bin/bash
scriptdir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
ssh root@localhost /usr/local/bin/docker run --rm \
    -v $scriptdir/src:$scriptdir/src \
    -v $scriptdir/workspace:$scriptdir/workspace \
    -w $scriptdir/workspace/build \
    clang:latest make
