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

static llvm::cl::OptionCategory ToolCategory("finder options");

struct CallExprHandler : public MatchFinder::MatchCallback {

    const DeclRefExpr *get_fp_variable_call(const CallExpr *expr){
        // This gets the DeclRefExpr for function pointers which are 
        // available directly on the stack, but not those which are accessed via
        // structure members.
        const ImplicitCastExpr *ice = dyn_cast<ImplicitCastExpr>(expr->getCallee());
        if (!ice)
            return 0;
        return dyn_cast<DeclRefExpr>(ice->getSubExpr());
    }

    virtual void run(const MatchFinder::MatchResult &result) {

        ASTContext *context = result.Context;

        const Expr *expr = nullptr;
        const CallExpr *callexpr = result.Nodes.getNodeAs<CallExpr>("callExpr");
        if (!callexpr)
            return;
        //node = get_fp_variable_call(expr);
        const ImplicitCastExpr *ice = dyn_cast<ImplicitCastExpr>(callexpr->getCallee());
        if (!ice)
            return;
        const DeclRefExpr *dre = dyn_cast<DeclRefExpr>(ice->getSubExpr());
        if (dre) {
            // function pointer held directly on stack var, no dereferening.
            llvm::outs() << "Function ptr as parameter ? ";
            expr = dre;
        } else {

            while (ice) {

                const Expr *ex = nullptr;
                const MemberExpr *me = nullptr;
                const DeclRefExpr *de = nullptr;

                ex = ice->getSubExpr();
                if (!ex) {
                    break;
                }
                me = dyn_cast<MemberExpr>(ex);
                if (!me) {
                    de = dyn_cast<DeclRefExpr>(ex);
                    de->dump();
                    expr = de;
                    break;
                }

                const DeclarationNameInfo dni = me->getMemberNameInfo();
                llvm::outs() << "MemberName(" << dni.getAsString() << "); ";
                llvm::outs() << "MemberType(" << me->getMemberDecl()->getType().getAsString() << "); ";
                ice = dyn_cast<ImplicitCastExpr>(me->getBase());
            }
        }

        if (expr) {

            FullSourceLoc loc = context->getFullLoc(expr->getLocStart());
            if (loc.isValid()) {
                expr->dumpPretty(*context); // same as getCallee ?
                // expr->dump(); // same as getCallee ?
                llvm::outs() << "; " << loc.getSpellingLineNumber() << ":"
                             << loc.getSpellingColumnNumber() << "\n";

            }
        }
    }
};

/*
                if (false){
                const Expr *callee = expr->getCallee();
                QualType q = expr->getType(); // return type
                //expr->dumpPretty(*context);
                if (callee) {
                    callee->dumpPretty(*context);
                    llvm::outs() << "; "
                                << loc.getSpellingLineNumber() << ":"
                                << loc.getSpellingColumnNumber() << "\n";
                    callee->dump();
                }
                }


                // gets the type of the function pointer, which is just it's signature.
                //<< callee->getType().getAsString() << "; "

                //llvm::outs() << "; " << next->getType().getAsString() << "\n";

                //llvm::outs() << "; " <<  callee->
                //llvm::outs()    << "; " << q.getAsString() << "; "
                //                << "; "
                //                << loc.getSpellingLineNumber() << ":"
                //                << loc.getSpellingColumnNumber() << "\n";
                ////expr->printPretty(llvm::outs());
                //expr->dump();

*/

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
