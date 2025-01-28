#include "Sema.h"
#include "llvm/ADT/StringSet.h"

// Semantic Analysis

namespace {
    class DeclCheck : public ASTVisitor {
        llvm::StringSet<> Scope;
        bool HasError;

        enum ErrorType { Twice, Not };

        void error(ErrorType ET, llvm::StringRef V) {
            llvm::errs() << "Variable " << V << " "
                         << (ET == Twice ? "already" : "not")
                         << " declared\n";
            HasError = true;
        }

    public:
        DeclCheck() : HasError(false) {}

        bool hasError() { return HasError; }

        virtual void visit(Factor &Node) override {
            if (Node.getKind() == Factor::Ident) {
                if (Scope.find(Node.getVal()) == Scope.end()) {
                    error(Not, Node.getVal());
                }
            }
        };

        virtual void visit(BinaryOp &Node) override {
            if (Node.getLeft()) Node.getLeft()->accept(*this);
            else HasError = true;
            if (Node.getRight()) Node.getRight()->accept(*this);
            else HasError = true;
        };

        virtual void visit(WithDecl &Node) override {
            for (auto It = Node.begin(), E = Node.end(); It != E; ++It) {
                if (!Scope.insert(*It).second) error(Twice, *It);
            }
            if (Node.getExpr()) Node.getExpr()->accept(*this);
            else HasError = true;
        };
    };
}

bool Sema::semantic(AST *Tree) {
    if (!Tree) return false;
    DeclCheck Check;
    Tree->accept(Check);
    return Check.hasError();
}