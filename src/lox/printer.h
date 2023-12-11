#ifndef PRINTER_H
#define PRINTER_H
#include "expression.h"
#include "stmt.h"

class Printer : public AstVisitor {
public:
    Printer() = default;
    VisitorAbsResult::ptr visit(BinaryExpr* expr) override;
    VisitorAbsResult::ptr visit(UnaryExpr* expr) override;
    VisitorAbsResult::ptr visit(GroupExpr* expr) override;
    VisitorAbsResult::ptr visit(LiteralExpr* expr) override;
    VisitorAbsResult::ptr visit(PrintStmt* expr) override;
    VisitorAbsResult::ptr visit(ExprStmt* expr) override;

};

#endif // PRINTER_H