
add_executable (findif findif.cpp)
set_property(TARGET findif PROPERTY CXX_STANDARD 11)
target_link_libraries (findif
    clangTooling)
