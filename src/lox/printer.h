#ifndef PRINTER_H
#define PRINTER_H
#include "expression.h"

class Printer : public ExprVisitor {
public:
    VisitorAbsResult::ptr visit(BinaryExpr* expr) override;

};

#endif // PRINTER_H