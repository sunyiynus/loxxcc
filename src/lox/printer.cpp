#include "printer.h"
#include <memory>


AnyResult::ptr Printer::visit(BinaryExpr* expr)
{
    AnyResult::ptr res = AnyResult::create();
    auto lRes = expr->lOperand->accept(this);
    auto rRes = expr->rOperand->accept(this);
    res->resultStr =  lRes->resultStr + " " + expr->op.literal + " " + rRes->resultStr;
    return res;
}

AnyResult::ptr Printer::visit(UnaryExpr* expr)
{
    AnyResult::ptr res = AnyResult::create();
    auto rRes = expr->rOperand->accept(this);
    res->resultStr = expr->op.lexeme + " " + rRes->resultStr;
    return res;
}

AnyResult::ptr Printer::visit(GroupExpr* expr)
{
    AnyResult::ptr res = AnyResult::create();
    auto sRes = expr->subExpr->accept(this);
    res->resultStr =  "( " + sRes->resultStr + " )";
    return res;
}

AnyResult::ptr Printer::visit(LiteralExpr* expr)
{
    AnyResult::ptr res = AnyResult::create();
    res->resultStr = expr->literal.literal;
    return res;
}

AnyResult::ptr Printer::visit(Variable* expr)
{
    AnyResult::ptr res = AnyResult::create();
    res->resultStr = expr->literal.literal;
    return res;
}

AnyResult::ptr Printer::visit(AssignExpr* expr)
{
    AnyResult::ptr res = AnyResult::create();
    return res;
}

AnyResult::ptr Printer::visit(PrintStmt* expr)
{
    AnyResult::ptr res = AnyResult::create();
    return res;
}

AnyResult::ptr Printer::visit(ExprStmt* expr)
{
    AnyResult::ptr res = AnyResult::create();
    return res;
}


AnyResult::ptr Printer::visit(BlockStmt* expr)
{
    AnyResult::ptr res = AnyResult::create();
    return res;
}


AnyResult::ptr Printer::visit(StmtDecl* expr)
{
    AnyResult::ptr res = AnyResult::create();
    return res;
}


AnyResult::ptr Printer::visit(VarDecl* expr)
{
    AnyResult::ptr res = AnyResult::create();
    return res;
}