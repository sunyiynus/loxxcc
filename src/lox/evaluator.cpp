#include "evaluator.h"
#include <memory>
#include "visitor_instance.h"



VisitorAbsResult::ptr Interpreter::visit(BinaryExpr* expr)
{
    VisitorAbsResult::ptr res = VisitorAbsResult::create();
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