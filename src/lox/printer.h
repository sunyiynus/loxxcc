#ifndef PRINTER_H
#define PRINTER_H
#include "expression.h"
#include "stmt.h"

class Printer : public InterpreteVisitor {
public:
    Printer() = default;
    AnyResult::ptr visit(BinaryExpr* expr) override;
    AnyResult::ptr visit(UnaryExpr* expr) override;
    AnyResult::ptr visit(GroupExpr* expr) override;
    AnyResult::ptr visit(LiteralExpr* expr) override;
    AnyResult::ptr visit(AssignExpr* expr) override;
    AnyResult::ptr visit(PrintStmt* expr) override;
    AnyResult::ptr visit(ExprStmt* expr) override;
    AnyResult::ptr visit(BlockStmt* expr) override;
    AnyResult::ptr visit(VarDecl* expr) override;
    AnyResult::ptr visit(StmtDecl* expr) override;


};

#endif // PRINTER_H