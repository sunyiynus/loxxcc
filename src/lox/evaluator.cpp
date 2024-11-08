#include "evaluator.h"
#include <memory>
#include "types.h"
#include "visitor_instance.h"
#include "expression.h"





AnyResult::ptr Interpreter::visit(BinaryExpr* expr)
{
    AnyResult::ptr l_res = expr->lOperand->accept(this);
    AnyResult::ptr r_res = expr->lOperand->accept(this);
    if (expr->op.token == TokenType::PLUS) {
    }


    if (l_res->type == prim_type::String) {
        try {
            number res = std::stold(l_res->value.get<std::string>());
        } catch (const std::exception& e) {
            
        }
    }

    if (r_res->type == prim_type::String) {
        
    }

    AnyResult::ptr res;
    return res;
}

AnyResult::ptr Interpreter::visit(UnaryExpr* expr)
{
    AnyResult::ptr res = AnyResult::create();
    AnyResult::ptr res_oprd = expr->rOperand->accept(this);
    if (res_oprd->type == prim_type::String) {
        number val = 0;
        try {
            val = std::stold(res_oprd->value.get<std::string>());
        } catch (const std::exception& e) {
            // TODO Throw expcetion
        }
        res->value = Any(-(val));
        res->type = prim_type::Number;
    } else if (res_oprd->type == prim_type::Number) {
        res->value = Any(-res_oprd->value.get<number>());
    }
    return res;
}

AnyResult::ptr Interpreter::visit(GroupExpr* expr)
{
    AnyResult::ptr group_res = expr->subExpr->accept(this);
    return group_res;
}

AnyResult::ptr Interpreter::visit(LiteralExpr* expr)
{
    AnyResult::ptr res = AnyResult::create();
    if (expr->literal.token == TokenType::NUMBER) {
        res->type = prim_type::Number;
        auto tmp = std::stold(expr->literal.lexeme);
        res->value = Any(tmp);
    } else if (expr->literal.token == TokenType::STRING) {
        res->type = prim_type::String;
        res->value = Any(expr->literal.lexeme);
        
    } else if (expr->literal.token == TokenType::IDENTIFIER) {
        // search in environment
        res->type = prim_type::String;
        res->value = Any(expr->literal.lexeme);
        
    }
    return res;
}

AnyResult::ptr Interpreter::visit(PrintStmt* expr)
{
    AnyResult::ptr res = AnyResult::create();
    return res;
}

AnyResult::ptr Interpreter::visit(ExprStmt* expr)
{
    AnyResult::ptr res = AnyResult::create();
    return res;
}

AnyResult::ptr Interpreter::visit(AssignExpr* expr)
{
    AnyResult::ptr res = AnyResult::create();
    return res;
}

AnyResult::ptr Interpreter::visit(DeclStmt* expr)
{
    AnyResult::ptr res = AnyResult::create();
    return res;
}