#include "evaluator.h"
#include <memory>
#include "visitor_instance.h"
#include "expression.h"



VisitorAbsResult::ptr Interpreter::visit(BinaryExpr* expr)
{
    VisitorAbsResult::ptr l_res = expr->lOperand->accept(this);
    VisitorAbsResult::ptr r_res = expr->lOperand->accept(this);
    if (expr->op.token == TokenType::PLUS) {
        l_res->value.get();
    }

    VisitorAbsResult::ptr res;
    return res;
}

VisitorAbsResult::ptr Interpreter::visit(UnaryExpr* expr)
{
    VisitorAbsResult::ptr res = VisitorAbsResult::create();
    return res;
}

VisitorAbsResult::ptr Interpreter::visit(GroupExpr* expr)
{
    VisitorAbsResult::ptr res = VisitorAbsResult::create();
    return res;
}

VisitorAbsResult::ptr Interpreter::visit(LiteralExpr* expr)
{
    VisitorAbsResult::ptr res = VisitorAbsResult::create();
    return res;
}

VisitorAbsResult::ptr Interpreter::visit(PrintStmt* expr)
{
    VisitorAbsResult::ptr res = VisitorAbsResult::create();
    return res;
}

VisitorAbsResult::ptr Interpreter::visit(ExprStmt* expr)
{
    VisitorAbsResult::ptr res = VisitorAbsResult::create();
    return res;
}

VisitorAbsResult::ptr Interpreter::visit(AssignExpr* expr)
{
    VisitorAbsResult::ptr res = VisitorAbsResult::create();
    return res;
}

VisitorAbsResult::ptr Interpreter::visit(DeclStmt* expr)
{
    VisitorAbsResult::ptr res = VisitorAbsResult::create();
    return res;
}