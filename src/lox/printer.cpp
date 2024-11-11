#include "printer.h"
#include <memory>

void Printer::setOutput(std::ostream& out)
{
    output = std::reference_wrapper<std::ostream>(out);
}

AnyResult::ptr Printer::visit(BinaryExpr* expr)
{
    AnyResult::ptr res = AnyResult::create();
    auto lRes = expr->lOperand->accept(this);
    auto rRes = expr->rOperand->accept(this);
    res->resultStr =  lRes->resultStr + " " + expr->op.literal + " " + rRes->resultStr;

    auto nodeId = getExprId(expr);
    oss << "  " << nodeId << " [label=\"BinaryExpr " << expr->op.lexeme << "\"];\n";
    auto leftId = getExprId(expr->lOperand.get());
    oss << "  " << nodeId << " -> " << leftId << ";\n";
    auto rightId = getExprId(expr->rOperand.get());
    oss << "  " << nodeId << " -> " << rightId << ";\n";
    return res;
}

AnyResult::ptr Printer::visit(UnaryExpr* expr)
{
    AnyResult::ptr res = AnyResult::create();
    auto rRes = expr->rOperand->accept(this);
    res->resultStr = expr->op.lexeme + " " + rRes->resultStr;

    auto nodeId = getExprId(expr);
    oss << "  " << nodeId << " [label=\"UnaryEpxr " << expr->op.lexeme << "\"];\n";
    auto rightId = getExprId(expr->rOperand.get());
    oss << "  " << nodeId << " -> " << rightId << ";\n";

    return res;
}

AnyResult::ptr Printer::visit(GroupExpr* expr)
{
    AnyResult::ptr res = AnyResult::create();
    auto sRes = expr->subExpr->accept(this);
    res->resultStr =  "( " + sRes->resultStr + " )";

    auto nodeId = getExprId(expr);
    oss << "  " << nodeId << " [label=\"GroupExpr " << "(  )" << "\"];\n";
    auto rightId = getExprId(expr->subExpr.get());
    oss << "  " << nodeId << " -> " << rightId << ";\n";
    return res;
}

AnyResult::ptr Printer::visit(LiteralExpr* expr)
{
    AnyResult::ptr res = AnyResult::create();
    auto nodeId = getExprId(expr);
    oss << "  " << nodeId << " [label=\"Litreal" << expr->literal.lexeme << "\"];\n";
    
    return res;
}

AnyResult::ptr Printer::visit(Variable* expr)
{
    AnyResult::ptr res = AnyResult::create();
    res->resultStr = expr->literal.literal;

    auto nodeId = getExprId(expr);
    oss << "  " << nodeId << " [label=\"Variable " << expr->literal.lexeme << "\"];\n";
    return res;
}

AnyResult::ptr Printer::visit(AssignExpr* expr)
{
    auto res = expr->expression->accept(this);
    auto nodeId = getExprId(expr);
    oss << "  " << nodeId << " [label=\"AssignExpr " << expr->literal.lexeme <<" =" << "\"];\n";
    auto rightId = getExprId(expr->expression.get());
    oss << "  " << nodeId << " -> " << rightId << ";\n";
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
    AnyResult::ptr res = expr->stmt->accept(this);
    return res;
}


AnyResult::ptr Printer::visit(VarDecl* expr)
{
    AnyResult::ptr res = AnyResult::create();
    return res;
}