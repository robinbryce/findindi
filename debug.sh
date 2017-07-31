#!/bin/bash
scriptdir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
# --network="host"
ssh -t root@localhost /usr/local/bin/docker run --rm -it \
    -p 3000:3000 \
    -v $scriptdir/src:$scriptdir/src \
    -v $scriptdir/workspace:$scriptdir/workspace \
    -w $scriptdir/workspace/build \
    clang:latest \
    /usr/bin/lldb-server platform --listen "*:3000"
