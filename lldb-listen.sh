#!/bin/bash
scriptdir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
source $scriptdir/sharedfuncs.sh
escalate="$(choose_privilege_escalate)"

# --network="host" - no difference
# With --security-opt seccomp:unconfined I can docker exec in and use lldb
# to "remote debug" with this lldb-server. It wasn't enough to fix it from the
# host.
DOCKER=$(which docker)
#ssh -t root@localhost ${DOCKER} run --rm -it \
$escalate $DOCKER run --rm -it \
    --security-opt seccomp:unconfined \
    -p 127.0.0.1:3000:3000 \
    -v $scriptdir/src:$scriptdir/src \
    -v $scriptdir/workspace:$scriptdir/workspace \
    -w $scriptdir/workspace/build \
    clang:latest \
    /usr/bin/lldb-server platform --listen "*:3000" --log-file=lldb-server.log
