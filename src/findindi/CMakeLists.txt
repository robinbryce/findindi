add_executable (findif findif.cpp)
set_property(TARGET findif PROPERTY CXX_STANDARD 11)

# 72 link errors with just these two
#    LLVM
#    clangTooling
# Some of these will be redundant. I haven't established which yet.

target_link_libraries (findif
    LLVM
    clangTooling
    clangFrontendTool
    clangFrontend
    clangDriver
    clangSerialization
    clangCodeGen
    clangParse
    clangSema
    clangStaticAnalyzerFrontend
    clangStaticAnalyzerCheckers
    clangStaticAnalyzerCore
    clangAnalysis
    clangARCMigrate
    clangRewriteFrontend
    clangEdit
    clangAST
    clangLex
    clangBasic
    )

# Not found
#    clangRewriteCore


