#include "interpreter.h"
#include <memory>
#include <limits>
#include "types.h"
#include "errors.h"
#include "Utility.h"
#include "visitor_instance.h"



template <typename T>
static T binary_operator_arithmetic(const Token& tk, T loprd, T roprd)
{
    T cnt_res = {0};
    switch (tk.token)
    {
    case TokenType::PLUS:
        cnt_res =  loprd + roprd; break;
    case TokenType::MINUS:
        cnt_res =  loprd - roprd; break;
    case TokenType::SLASH:
        cnt_res =  loprd / roprd; break;
    case TokenType::STAR:
        cnt_res =  loprd * roprd; break;
    case TokenType::PERCENT:
        cnt_res =  static_cast<number>((static_cast<long int>(loprd) % static_cast<long int>(roprd))); break;
    default:
        throw bad_operator(std::string("Unknow operator: ") + tk.lexeme);
        break;
    }
    return cnt_res;
}

template <typename T>
static bool binary_operator_comparsion(const Token& tk, const T& loprd, const T& roprd)
{
    bool cnt_res = {0};
    switch (tk.token) {
    case TokenType::EQUAL_EQUAL:
        cnt_res = false;
        if (std::numeric_limits<T>::epsilon() > (loprd - roprd)) {
            cnt_res = true;
        }
        break;
    case TokenType::BANG_EQUAL:
        cnt_res = true;
        if (std::numeric_limits<T>::epsilon() > (loprd - roprd)) {
            cnt_res = false;
        }
        break;
    case TokenType::GREATER_EQUAL:
        cnt_res =  loprd >= roprd; break;
    case TokenType::LESS_EQUAL:
        cnt_res =  loprd <= roprd; break;
    case TokenType::GREATER:
        cnt_res =  loprd > roprd; break;
    case TokenType::LESS:
        cnt_res =  loprd < roprd; break;
    default:
        throw bad_operator(std::string("Unknow operator: {}") + tk.lexeme);
        break;
    }
    return cnt_res;
}

static bool comparsion_operator(const TokenType type)
{
    std::initializer_list<TokenType> comparsionType {
        TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL,
        TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL
    };
    return Utility::match(comparsionType, type);
}

static number arithmetic_operator(const TokenType type)
{
    std::initializer_list<TokenType> comparsionType {
        TokenType::PLUS, TokenType::MINUS, TokenType::SLASH, TokenType::STAR,
        TokenType::PERCENT
    };
    return Utility::match(comparsionType, type);
}

void Interpreter::setOutput(std::ostream& out)
{
    output = std::reference_wrapper<std::ostream>(out);
}


void Interpreter::interprete(const std::vector<AbsStmt::ptr>& stmts)
{
    for (const auto& stmt: stmts) {
        if (stmt){
            execute(stmt);
        }
    }
}

void Interpreter::execute(AbsStmt::ptr stmt)
{
    stmt->accept(this);
}

AnyResult::ptr Interpreter::evaluate(AbsExpr::ptr expr)
{
    return expr->accept(this);
}

AnyResult::ptr Interpreter::findSymbol(const std::string& symbol)
{
    std::shared_ptr<Environment> tmpEnv = scopedEnvChain;
    while (tmpEnv) {
        if (tmpEnv->haveSymbol(symbol)) {
            return tmpEnv->get(symbol);
        }
        tmpEnv = tmpEnv->parentEnv;
    }
    return nullptr;
}


AnyResult::ptr Interpreter::visit(BinaryExpr* expr)
{
    AnyResult::ptr l_res = expr->lOperand->accept(this);
    AnyResult::ptr r_res = expr->rOperand->accept(this);
    AnyResult::ptr res = AnyResult::create();
    const Token& tk = expr->op;

    if (l_res->type == prim_type::String && r_res->type == prim_type::String) {
        if (tk.token == TokenType::PLUS) {
            res->value = Any(l_res->value.get<std::string>() + r_res->value.get<std::string>());
            res->type = prim_type::String;
            return res;
        } else {
            throw bad_oprand(std::string("String can not operand on ") + expr->op.lexeme);
        }
    }

    if (l_res->type == prim_type::Number && r_res->type == prim_type::Number) {
        number cnt_res = 0;
        number loprd = l_res->value.get<number>();
        number roprd = r_res->value.get<number>();
        if (arithmetic_operator(tk.token)) {
            number tmp = binary_operator_arithmetic(tk, loprd, roprd);
            res->type = prim_type::Number;
            res->value = Any(tmp);
        } else if (comparsion_operator(tk.token)) {
            bool tmp = binary_operator_comparsion(tk, loprd, roprd);
            res->type = prim_type::Boolean;
            res->value = Any(tmp);
        }
        return res;
    }

    return res;
}

AnyResult::ptr Interpreter::visit(UnaryExpr* expr)
{
    AnyResult::ptr res = AnyResult::create();
    AnyResult::ptr res_oprd = expr->rOperand->accept(this);
    const auto& tk = expr->op;
    number tmpValue = 0;
    bool numericFlag = false;
    if (res_oprd->type == prim_type::String) {
        try {
            tmpValue = std::stold(res_oprd->value.get<std::string>());
            numericFlag = true;
        } catch (const std::exception& e) {
            // TODO Throw expcetion
        }
    } else if (res_oprd->type == prim_type::Number) {
        tmpValue = res_oprd->value.get<number>();
        numericFlag = true;
    }
    

    if (res_oprd->type == prim_type::Boolean) {
        if (tk.token == TokenType::BANG) {
            res->value = Any(!(res_oprd->value.get<bool>()));
            res->type = prim_type::Boolean;
        } else {
            throw bad_operator(std::string("Can't use that operator ") + tk.lexeme);
        }
        return res;
    }

    if (numericFlag) {
        if (tk.token == TokenType::MINUS) {
            res->value = Any(-tmpValue);
        } else if (tk.token == TokenType::BANG) {
            auto tmp = tmpValue;
            auto tmp_res = false;
            if (tmp < std::numeric_limits<number>::epsilon()) {
                tmp_res = true;
            }
            res->value = Any(tmp_res);
            res->type = prim_type::Boolean;
        }
    }

    return res;
}

AnyResult::ptr Interpreter::visit(GroupExpr* expr)
{
    return expr->subExpr->accept(this);
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
    }
    return res;
}


AnyResult::ptr Interpreter::visit(Variable* expr)
{
    AnyResult::ptr res;
    if (expr->literal.token == TokenType::IDENTIFIER) {
        // search in environment
        res = findSymbol(expr->literal.lexeme);
    }
    return res;
}

AnyResult::ptr Interpreter::visit(AssignExpr* expr)
{
    AnyResult::ptr res;
    if (expr->expression) {
        auto val = evaluate(expr->expression);
        auto oldVal = findSymbol(expr->literal.lexeme);
        if (val) {
            oldVal->type = val->type;
            oldVal->value = val->value;
        }
        res = val;
    }
    return res;
}

AnyResult::ptr Interpreter::visit(PrintStmt* expr)
{
    auto tmpRes = expr->expression->accept(this);
    if (tmpRes) {
        auto& tmp = *tmpRes.get();
        output.get() << static_cast<std::string>(tmp) << "\n";
    }
    return nullptr;
}


AnyResult::ptr Interpreter::visit(BlockStmt* expr)
{
    auto blkEnv = std::make_shared<Environment>(scopedEnvChain);
    scopedEnvChain = blkEnv;
    for (const auto& stmt : expr->stmts) {
        execute(stmt);
    }
    scopedEnvChain = blkEnv->parentEnv;
    return nullptr;
}

AnyResult::ptr Interpreter::visit(ExprStmt* expr)
{
    return expr->expression->accept(this);
}


AnyResult::ptr Interpreter::visit(VarDecl* expr)
{
    auto key = expr->identifier.lexeme;
    if (expr->expression) {
        auto val = evaluate(expr->expression);
        scopedEnvChain->define(key, val);
    } else {
        auto val = AnyResult::create();
        scopedEnvChain->define(key, val);
    }
    return nullptr;
}


AnyResult::ptr Interpreter::visit(StmtDecl* expr)
{
    return expr->stmt->accept(this);
}