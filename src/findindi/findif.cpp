#include "clang/Tooling/CommonOptionsParser.h"
#include "llvm/Support/CommandLine.h"

using namespace clang::tooling;

static llvm::cl::OptionCategory ToolCategory("finder options");

int main(int argc, const char **argv) {
    CommonOptionsParser OptionsParser(argc, argv, ToolCategory);
}