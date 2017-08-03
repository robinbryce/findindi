#!/bin/bash
set -e
scriptdir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

source $scriptdir/sharedfuncs.sh
escalate="$(choose_privilege_escalate)"

$escalate mkdir -p $scriptdir/../workspace/build/examples
$escalate cp $scriptdir/src/examples/*.c $scriptdir/../workspace/build/examples/

DOCKER=$(which docker)
$escalate $DOCKER run --rm \
    -v $scriptdir/src:$scriptdir/src \
    -v $scriptdir/scripts:$scriptdir/scripts \
    -v $scriptdir/workspace:$scriptdir/workspace \
    -w $scriptdir/workspace/build \
    clang:latest make
