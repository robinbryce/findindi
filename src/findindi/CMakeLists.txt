#add_executable (findif findif.cpp)
add_executable (findindicall findindicall.cpp)
set_property(TARGET findindicall PROPERTY CXX_STANDARD 11)

# 72 link errors with just these two
#    LLVM
#    clangTooling
# Some of these will be redundant. I haven't established which yet.

target_link_libraries (findindicall
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
    clangASTMatchers
    clangLex
    clangBasic
    )

# Not found
#    clangRewriteCore


