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
    oss << "  " << nodeId << " [label=\"Litreal " << expr->literal.lexeme << "\"];\n";
    
    return res;
}

AnyResult::ptr Printer::visit(CallExpr* expr)
{

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
    expr->expression->accept(this);
    auto nodeId = getStmtId(expr);
    oss << "  " << nodeId << " [label=\"PrintStmt " << "" << "\"];\n";
    auto rightId = getExprId(expr->expression.get());
    oss << "  " << nodeId << " -> " << rightId << ";\n";
    return res;
}

AnyResult::ptr Printer::visit(ExprStmt* expr)
{
    AnyResult::ptr res = AnyResult::create();
    expr->expression->accept(this);
    auto nodeId = getStmtId(expr);
    oss << "  " << nodeId << " [label=\"ExprStmt " << "" << "\"];\n";
    auto rightId = getExprId(expr->expression.get());
    oss << "  " << nodeId << " -> " << rightId << ";\n";
    return res;
}


AnyResult::ptr Printer::visit(ReturnStmt* expr)
{
    expr->expression->accept(this);
    auto nodeId = getStmtId(expr);
    oss << "  " << nodeId << " [label=\"ReturnStmt " << "" << "\"];\n";
    auto rightId = getExprId(expr->expression.get());
    oss << "  " << nodeId << " -> " << rightId << ";\n";
    return nullptr;
}


AnyResult::ptr Printer::visit(BlockStmt* expr)
{
    AnyResult::ptr res = AnyResult::create();
    auto nodeId = getStmtId(expr);
    oss << "  " << nodeId << " [label=\"BlockStmt " << "" << "\"];\n";
    for (const auto& stmt : expr->stmts) {
        stmt->accept(this);
        auto rightId = getStmtId(stmt.get());
        oss << "  " << nodeId << " -> " << rightId << ";\n";
    }
    return res;
}


AnyResult::ptr Printer::visit(StmtDecl* expr)
{
    AnyResult::ptr res = expr->stmt->accept(this);
    auto nodeId = getStmtId(expr);
    oss << "  " << nodeId << " [label=\"StmtDecl " << "" << "\"];\n";
    auto rightId = getStmtId(expr->stmt.get());
    oss << "  " << nodeId << " -> " << rightId << ";\n";
    return res;
}


AnyResult::ptr Printer::visit(VarDecl* expr)
{
    AnyResult::ptr res = AnyResult::create();
    auto nodeId = getStmtId(expr);
    if (expr->expression) {
        oss << "  " << nodeId << " [label=\"VarDecl var " << expr->identifier.lexeme << " = " << "\"];\n";
        expr->expression->accept(this);
        auto rightId = getExprId(expr->expression.get());
        oss << "  " << nodeId << " -> " << rightId << ";\n";
    }else {
        oss << "  " << nodeId << " [label=\"VarDecl var " << expr->identifier.lexeme << ";\"];\n";
    }
    return res;
}

AnyResult::ptr Printer::visit(ClassDecl* decl)
{
    // auto nodeId = getStmtId(expr);
    // oss << "  " << nodeId << " [label=\"ReturnStmt " << "" << "\"];\n";
    // auto rightId = getExprId(expr->expression.get());
    // oss << "  " << nodeId << " -> " << rightId << ";\n";
}

AnyResult::ptr Printer::visit(FuncDecl* decl)
{
    auto nodeId = getStmtId(decl);
    oss << "  " << nodeId << " [label=\"FuncDecl " << decl->funcName.lexeme << "\"];\n";
    for (const auto& stmt : decl->stmts) {
        stmt->accept(this);
        auto rightId = getStmtId(stmt.get());
        oss << "  " << nodeId << " -> " << rightId << ";\n";
    }
    return nullptr;
}

AnyResult::ptr Printer::visit(IfStmt* stmt)
{
    defineNode(getStmtId(stmt), "IfStmt", "");
    stmt->checkExpression->accept(this);
    auto nodeId = getStmtId(stmt);
    pointTo(nodeId, getExprId(stmt->checkExpression.get()));

    auto tureNode = ++idCounter;
    auto falseNode = ++idCounter;
    pointTo(nodeId, tureNode);
    defineNode(tureNode, "TrueStmts", "");
    defineNode(falseNode, "FalseStmts", "");

    for (const auto& stmt : stmt->trueStmts) {
        stmt->accept(this);
        pointTo(tureNode, getStmtId(stmt.get()));
    }

    for (const auto& stmt : stmt->elseStmts) {
        stmt->accept(this);
        pointTo(falseNode, getStmtId(stmt.get()));
    }
    return nullptr;
}


AnyResult::ptr Printer::visit(ForStmt* stmt)
{
    defineNode(getStmtId(stmt), "ForStmt", "");
    auto nodeId = getStmtId(stmt);
    stmt->initializationStmt->accept(this);
    stmt->conditionExpr->accept(this);
    stmt->updateStmt->accept(this);
    pointTo(nodeId, getStmtId(stmt->initializationStmt.get()));
    pointTo(nodeId, getExprId(stmt->conditionExpr.get()));
    pointTo(nodeId, getStmtId(stmt->updateStmt.get()));
    auto stmtsNode = ++idCounter;
    defineNode(stmtsNode, "Stmts", "");
    pointTo(nodeId, stmtsNode);
    for (const auto& stmt : stmt->stmts) {
        stmt->accept(this);
        pointTo(stmtsNode, getStmtId(stmt.get()));
    }
    return nullptr;
}


AnyResult::ptr Printer::visit(WhileStmt* stmt)
{
    auto nodeId = getStmtId(stmt);
    defineNode(nodeId, "WhileStmt", "");
    stmt->condition->accept(this);
    pointTo(nodeId, getExprId(stmt->condition.get()));
    auto stmtsNode = ++idCounter;
    defineNode(stmtsNode, "Stmts", "");
    pointTo(nodeId, stmtsNode);
    for (const auto& stmt : stmt->stmts) {
        stmt->accept(this);
        pointTo(stmtsNode, getStmtId(stmt.get()));
    }
}
