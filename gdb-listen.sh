#!/bin/bash
scriptdir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
# --network="host" - no difference
# With --security-opt seccomp:unconfined I can docker exec in and use lldb
# to "remote debug" with this lldb-server. It wasn't enough to fix it from the
# host.
source $scriptdir/sharedfuncs.sh
source $scriptdir/volumes.sh
escalate="$(choose_privilege_escalate)"

TARGET=$scriptdir/workspace/build/findindi/findindicall

DOCKER=$(which docker)
#ssh -t root@localhost ${DOCKER} run --rm -it \
$escalate $DOCKER run --rm -it \
    --security-opt seccomp:unconfined \
    -p 127.0.0.1:3000:3000 \
    -v /projects/nshield-main:/projects/nshield-main \
    -v /projects/nshield-build:/projects/nshield-build \
    -v $scriptdir/src:$scriptdir/workspace/src \
    -v $scriptdir/workspace/scripts:$scriptdir/workspace/scripts \
    -v $scriptdir/workspace/build:$scriptdir/workspace/build \
    -w /projects/nshield-main \
    clang:latest \
    /usr/bin/gdbserver ":3000" "$@"
    #/usr/bin/gdbserver ":3000" $TARGET module/src/firmware/smartcard.c

