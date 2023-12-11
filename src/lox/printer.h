#ifndef PRINTER_H
#define PRINTER_H
#include "expression.h"

class Printer : public AstPrinter {
public:
    Printer() = default;
    VisitorAbsResult::ptr visit(BinaryExpr* expr) override;
    VisitorAbsResult::ptr visit(UnaryExpr* expr) override;
    VisitorAbsResult::ptr visit(GroupExpr* expr) override;
    VisitorAbsResult::ptr visit(LiteralExpr* expr) override;

};

#endif // PRINTER_H