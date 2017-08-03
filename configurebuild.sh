#!/bin/bash
scriptdir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
source $scriptdir/sharedfuncs.sh
escalate="$(choose_privilege_escalate)"
$escalate docker run --rm -it \
    -v $scriptdir/src:$scriptdir/src \
    -v $scriptdir/scripts:$scriptdir/scripts \
    -v $scriptdir/workspace:$scriptdir/workspace \
    -w $scriptdir/workspace \
    clang:latest ../scripts/genbuild.sh
