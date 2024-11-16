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

    defineNode(expr, "BinaryExpr", expr->op.lexeme);
    pointTo(expr, expr->lOperand.get());
    pointTo(expr, expr->rOperand.get());
    return res;
}

AnyResult::ptr Printer::visit(UnaryExpr* expr)
{
    AnyResult::ptr res = AnyResult::create();
    auto rRes = expr->rOperand->accept(this);
    res->resultStr = expr->op.lexeme + " " + rRes->resultStr;
    defineNode(expr, "UnaryExpr", expr->op.lexeme);
    pointTo(expr, expr->rOperand.get());
    return res;
}

AnyResult::ptr Printer::visit(GroupExpr* expr)
{
    AnyResult::ptr res = AnyResult::create();
    auto sRes = expr->subExpr->accept(this);
    res->resultStr =  "( " + sRes->resultStr + " )";

    defineNode(expr, "GroupExpr", "( )");
    pointTo(expr, expr->subExpr.get());
    return res;
}

AnyResult::ptr Printer::visit(LiteralExpr* expr)
{
    AnyResult::ptr res = AnyResult::create();
    defineNode(expr, "LiteralExpr", expr->literal.lexeme);
    return res;
}

AnyResult::ptr Printer::visit(CallExpr* expr)
{

}

AnyResult::ptr Printer::visit(Variable* expr)
{
    AnyResult::ptr res = AnyResult::create();
    res->resultStr = expr->literal.literal;
    defineNode(expr, "Var", expr->literal.lexeme);
    return res;
}

AnyResult::ptr Printer::visit(AssignExpr* expr)
{
    auto res = expr->expression->accept(this);
    defineNode(expr, "AssignExpr", expr->literal.lexeme);
    pointTo(expr, expr->expression.get());
    return res;
}

AnyResult::ptr Printer::visit(PrintStmt* expr)
{
    AnyResult::ptr res = AnyResult::create();
    expr->expression->accept(this);
    defineNode(expr, "PrintStmt");
    pointTo(expr, expr->expression.get());
    return res;
}

AnyResult::ptr Printer::visit(ExprStmt* expr)
{
    AnyResult::ptr res = AnyResult::create();
    expr->expression->accept(this);
    defineNode(expr, "ExprStmt");
    pointTo(expr, expr->expression.get());
    return res;
}


AnyResult::ptr Printer::visit(ReturnStmt* expr)
{
    expr->expression->accept(this);
    defineNode(expr, "ReturnStmt");
    pointTo(expr, expr->expression.get());
    return nullptr;
}


AnyResult::ptr Printer::visit(BlockStmt* expr)
{
    AnyResult::ptr res = AnyResult::create();
    auto id = defineNode(expr, "BlockStmt");
    iteralStmts(id, expr->stmts);
    return res;
}


AnyResult::ptr Printer::visit(StmtDecl* expr)
{
    AnyResult::ptr res = expr->stmt->accept(this);
    defineNode(expr, "StmtDecl");
    pointTo(expr, expr->stmt.get());
    return res;
}


AnyResult::ptr Printer::visit(VarDecl* expr)
{
    defineNode(expr, "VarDecl", expr->identifier.lexeme);
    if (expr->expression) {
        expr->expression->accept(this);
        pointTo(expr, expr->expression.get());
    }
    return nullptr;
}

AnyResult::ptr Printer::visit(ClassDecl* decl)
{
    // auto nodeId = getId(expr);
    // oss << "  " << nodeId << " [label=\"ReturnStmt " << "" << "\"];\n";
    // auto rightId = getId(expr->expression.get());
    // oss << "  " << nodeId << " -> " << rightId << ";\n";
}

AnyResult::ptr Printer::visit(FuncDecl* decl)
{
    defineNode(decl, "FuncDecl" , decl->funcName.lexeme);
    auto nodeId = appendNode(decl, "Stmts");
    iteralStmts(nodeId, decl->stmts);
    return nullptr;
}

AnyResult::ptr Printer::visit(IfStmt* stmt)
{
    defineNode(stmt, "IfStmt", "");
    stmt->checkExpression->accept(this);
    pointTo(stmt, stmt->checkExpression.get());
    auto tureNode = appendNode(stmt, "TrueStmts");
    auto falseNode = appendNode(stmt, "FalseStmts");
    iteralStmts(tureNode, stmt->trueStmts);
    iteralStmts(falseNode, stmt->elseStmts);
    return nullptr;
}



AnyResult::ptr Printer::visit(ForStmt* stmt)
{
    defineNode(stmt, "ForStmt", "");
    callAccept(stmt->initializationStmt);
    callAccept(stmt->conditionExpr);
    callAccept(stmt->updateStmt);
    pointTo(stmt, stmt->initializationStmt.get());
    pointTo(stmt, stmt->conditionExpr.get());
    pointTo(stmt, stmt->updateStmt.get());
    auto stmtsNode = appendNode(stmt, "Stmts");
    iteralStmts(stmtsNode, stmt->stmts);
    return nullptr;
}


AnyResult::ptr Printer::visit(WhileStmt* stmt)
{
    defineNode(stmt, "WhileStmt", "");
    stmt->condition->accept(this);
    pointTo(stmt, stmt->condition.get());
    auto stmtsNode = appendNode(stmt, "Stmts");
    iteralStmts(stmtsNode, stmt->stmts);
    return nullptr;
}
