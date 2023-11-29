#include "printer.h"



VisitorAbsResult::ptr Printer::visit(BinaryExpr* expr)
{
    VisitorAbsResult::ptr res = std::make_unique<VisitorAbsResult>();
    auto lRes = expr->lOperand->accept(this);
    auto rRes = expr->rOperand->accept(this);
    res->resultStr =  lRes->resultStr + " " + expr->op.lexeme + " " + rRes->resultStr;
    return res;
}
