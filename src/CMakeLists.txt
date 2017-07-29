cmake_minimum_required (VERSION 3.5.0)

# Path is correct for ubuntu 16:04 backports .deb packages for llvm-4.0 release
set(CMAKE_INCLUDE_PATH /usr/lib/llvm-4.0/include)
set(CMAKE_LIBRARY_PATH /usr/lib/llvm-4.0/lib)
set(CMAKE_PREFIX_PATH /opt/findindirect)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

# Tool chain configuration, we want clang
# currently doing this using -DCMAKE_xxx on cmake command line
#set(CMAKE_C_COMPILER /usr/bin/clang)
#set(CMAKE_CXX_COMPILER /usr/bin/clang++)

# Path is correct for ubuntu 16:04 backports .deb packages for llvm-4.0 release
include_directories(/usr/lib/llvm-4.0/include)

add_subdirectory (findindi)
