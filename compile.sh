#!/bin/bash
set -e
scriptdir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

sudo mkdir -p $scriptdir/workspace/build/examples
sudo cp $scriptdir/src/examples/*.c $scriptdir/workspace/build/examples/

ESCALATE=$(which really)
if [ "" = "$ESCALATE" ]; then
    ESCALATE="sudo"
fi
DOCKER=$(which docker)
$ESCALATE $DOCKER run --rm \
    -v $scriptdir/src:$scriptdir/src \
    -v $scriptdir/workspace:$scriptdir/workspace \
    -w $scriptdir/workspace/build \
    clang:latest make
