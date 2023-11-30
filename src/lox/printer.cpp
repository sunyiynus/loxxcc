#include "printer.h"
#include <memory>


VisitorAbsResult::ptr Printer::visit(BinaryExpr* expr)
{
    VisitorAbsResult::ptr res = VisitorAbsResult::create();
    auto lRes = expr->lOperand->accept(this);
    auto rRes = expr->rOperand->accept(this);
    res->resultStr =  lRes->resultStr + " " + expr->op.lexeme + " " + rRes->resultStr;
    return res;
}

VisitorAbsResult::ptr Printer::visit(UnaryExpr* expr)
{
    VisitorAbsResult::ptr res = VisitorAbsResult::create();
    auto rRes = expr->rOperand->accept(this);
    res->resultStr = expr->op.lexeme + " " + rRes->resultStr;
    return res;
}

VisitorAbsResult::ptr Printer::visit(GroupExpr* expr)
{
    VisitorAbsResult::ptr res = VisitorAbsResult::create();
    auto sRes = expr->subExpr->accept(this);
    res->resultStr =  "( " + sRes->resultStr + " )";
    return res;
}

VisitorAbsResult::ptr Printer::visit(LiteralExpr* expr)
{
    VisitorAbsResult::ptr res = VisitorAbsResult::create();
    res->resultStr = expr->literal.lexeme;
    return res;
}