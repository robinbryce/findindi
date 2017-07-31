#!/bin/bash
scriptdir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
# --network="host" - no difference
# With --security-opt seccomp:unconfined I can docker exec in and use lldb
# to "remote debug" with this lldb-server. It wasn't enough to fix it from the
# host.

ESCALATE=$(which really)
if [ "" = "$ESCALATE" ]; then
    ESCALATE="sudo"
fi

source $scriptdir/include_spec.sh

DOCKER=$(which docker)
#ssh -t root@localhost ${DOCKER} run --rm -it \
$ESCALATE $DOCKER run --rm -it \
    --security-opt seccomp:unconfined \
    -p 127.0.0.1:3000:3000 \
    $EXTRA_VOLUMES \
    -v $scriptdir/src:$scriptdir/src \
    -v $scriptdir/workspace:$scriptdir/workspace \
    -w $scriptdir/workspace/build \
    clang:latest \
    /usr/bin/gdbserver ":3000" findindi/findif /workspace/module/src/firmware/smartcard.c -- "$INCLUDE_SPEC"


