#!/bin/bash
scriptdir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
sudo docker run -it \
    -v $scriptdir/src:$scriptdir/src \
    -v $scriptdir/workspace:$scriptdir/workspace \
    -w $scriptdir/workspace \
    clang:latest bash
