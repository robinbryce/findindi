#include "clang/Tooling/CommonOptionsParser.h"
#include "llvm/Support/CommandLine.h"

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Tooling/Tooling.h"

// this tutorial: http://clang.llvm.org/docs/RAVFrontendAction.html
// and this one: https://kevinaboos.wordpress.com/2013/07/23/clang-tutorial-part-ii-libtooling-example/

using namespace clang;
using namespace clang::ast_matchers;


class FindIndirectCallVisitor : public RecursiveASTVisitor<FindIndirectCallVisitor> {
    public:
    explicit FindIndirectCallVisitor(ASTContext *context) : m_context(context) {}
    bool VisitCallExpr(CallExpr *expr){
        FullSourceLoc loc = m_context->getFullLoc(expr->getLocStart());
        if (loc.isValid())
            llvm::outs()    << "Found function call at "
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

struct CallExprHandler : public MatchFinder::MatchCallback {
    virtual void run(const MatchFinder::MatchResult &result) {

        const CallExpr *expr = result.Nodes.getNodeAs<CallExpr>("callExpr");
        if (expr) {
            ASTContext *context = result.Context;
            FullSourceLoc loc = context->getFullLoc(expr->getLocStart());
            if (loc.isValid()) {
                const Expr *next = expr->IgnoreImplicit();
                next->dumpPretty(*context); // same as getCallee ?
                llvm::outs() << "; " << next->getType().getAsString() << "\n";

                if (false){
                const Expr *callee = expr->getCallee();
                QualType q = expr->getType(); // return type
                //expr->dumpPretty(*context);
                if (callee) {
                    callee->dumpPretty(*context);
                    llvm::outs() << "; "
                                // gets the type of the function pointer, which is just it's signature.
                                //<< callee->getType().getAsString() << "; "
                                << loc.getSpellingLineNumber() << ":"
                                << loc.getSpellingColumnNumber() << "\n";
                    callee->dump();
                }
                }
                    //llvm::outs() << "; " <<  callee->
                //llvm::outs()    << "; " << q.getAsString() << "; "
                //                << "; "
                //                << loc.getSpellingLineNumber() << ":"
                //                << loc.getSpellingColumnNumber() << "\n";
                ////expr->printPretty(llvm::outs());
                //expr->dump();
                llvm::outs() << "\n";
            }
        }
    }
};

int main(int argc, const char **argv) {
    tooling::CommonOptionsParser op(argc, argv, ToolCategory);
    tooling::ClangTool tool(op.getCompilations(), op.getSourcePathList());
    //int result = tool.run(tooling::newFrontendActionFactory<FindIndirectCallAction>().get());
    CallExprHandler call_handler;
    MatchFinder finder;
    //finder.addMatcher(callExpr().bind("callExpr"), &call_handler);
    finder.addMatcher(callExpr(unless(hasDescendant(declRefExpr(hasType(functionType()))))).bind("callExpr"), &call_handler);
    int result = tool.run(tooling::newFrontendActionFactory(&finder).get());
    return result;
}
