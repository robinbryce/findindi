#!/bin/bash
scriptdir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
SOURCE=$scriptdir/llvm-trunk/utils/docker/debian8
# --docker-repository https://hub.docker.com/r/robinbryce/clang-poc
llvm-trunk/utils/docker/build_docker_image.sh \
    --source $SOURCE \
    --docker-repository robinbryce/clang-poc \
    --docker-tag latest \
    \
    -b branches/google/stable  \
    -p clang -i stage2-install-clang -i stage2-install-clang-headers \
    -- \
    -DLLVM_TARGETS_TO_BUILD=Native -DCMAKE_BUILD_TYPE=Release \
    -DBOOTSTRAP_CMAKE_BUILD_TYPE=Release \
    -DCLANG_ENABLE_BOOTSTRAP=ON \
    -DCLANG_BOOTSTRAP_TARGETS="install-clang;install-clang-headers"
