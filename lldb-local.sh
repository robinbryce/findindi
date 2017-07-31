#!/bin/bash
scriptdir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
# --network="host" - no difference
# With --security-opt seccomp:unconfined I can docker exec in and use lldb
# to "remote debug" with this lldb-server. It wasn't enough to fix it from the
# host.
#ssh -t root@localhost /usr/local/bin/docker run --rm -it \
ssh root@localhost /usr/local/bin/docker run --rm -i \
    --security-opt seccomp:unconfined \
    -p 127.0.0.1:3000:3000 \
    -v $scriptdir/src:$scriptdir/src \
    -v $scriptdir/workspace:$scriptdir/workspace \
    -w $scriptdir/workspace/build \
    clang:latest \
    /usr/bin/lldb-4.0 "$@"
