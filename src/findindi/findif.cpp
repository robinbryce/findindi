#include "clang/Tooling/CommonOptionsParser.h"
#include "llvm/Support/CommandLine.h"

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Tooling/Tooling.h"

// this tutorial: http://clang.llvm.org/docs/RAVFrontendAction.html
// and this one: https://kevinaboos.wordpress.com/2013/07/23/clang-tutorial-part-ii-libtooling-example/

using namespace clang;

class FindIndirectCallVisitor : public RecursiveASTVisitor<FindIndirectCallVisitor> {
    public:
    explicit FindIndirectCallVisitor(ASTContext *context) : m_context(context) {}
    bool VisitCXXRecordDecl(CXXRecordDecl *decl) {
        FullSourceLoc loc = m_context->getFullLoc(decl->getLocStart());
        if (loc.isValid())
            llvm::outs()    << "Found declaration at "
                            << loc.getSpellingLineNumber() << ":"
                            << loc.getSpellingColumnNumber() << "\n";
        return true;
    }
    private:
    ASTContext *m_context;
};

class FindIndirectCallConsumer : public clang::ASTConsumer {
    public:
    explicit FindIndirectCallConsumer(ASTContext *context) : m_visitor(context) {}
    virtual void HandleTranslationUnit(clang::ASTContext &context) {
        m_visitor.TraverseDecl(context.getTranslationUnitDecl());
    }
    private:
    FindIndirectCallVisitor m_visitor;
};

class FindIndirectCallAction : public clang::ASTFrontendAction {
    public:
    virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
        clang::CompilerInstance &compiler, llvm::StringRef in_file) {
            return std::unique_ptr<clang::ASTConsumer>(
                new FindIndirectCallConsumer(&compiler.getASTContext())
            );
        }
};

static llvm::cl::OptionCategory ToolCategory("finder options");

int main(int argc, const char **argv) {
    //tooling::CommonOptionsParser op(argc, argv, ToolCategory);
    if (argc > 1) {
        clang::tooling::runToolOnCode(new FindIndirectCallAction, argv[1]);
    }
}