#include "parser.h"
#include <functional>
#include <list>
#include "errors.h"
#include "format.h"

std::list<AbsStmt::ptr> Parser::parse() {
    std::list<AbsStmt::ptr> stmts;

    while (!atEnd()) {
        stmts.push_back(declaration());
    }
    return stmts;
}

const Token& Parser::current()
{
    return *curItr;
}


const Token& Parser::previous()
{
    auto tmpItr = curItr;
    tmpItr--;
    return *tmpItr;
}


bool Parser::atEnd() const {
    return curItr == tokensSeq.end();
}

bool Parser::matchTokens(std::initializer_list<TokenType> tktypes)
{
    auto tmpItr = curItr;
    for (auto tktype:tktypes) {
        if (!atEnd() && tmpItr->token == tktype) {
            return true;
        }
    }
    return false;
}

void Parser::advance()
{
    curItr++;
}


void Parser::synchronize()
{
    std::initializer_list<TokenType> matchTk {TokenType::RIGHT_BRACE, 
                                                TokenType::RIGHT_PAREN,
                                                TokenType::COMMA};
    while (!atEnd()) {
        if (matchTokens(matchTk))
        {
            break;
        }
        advance();
    }
}


void Parser::consume(std::initializer_list<TokenType> tktypes)
{
    if (matchTokens(tktypes)) {
        advance();
        return;
    }

    std::string error = "Have meet unexpect token: " + static_cast<std::string>(current());
    throw bad_grammar(error);
}

AbsExpr::ptr Parser::expression()
{
    if (matchTokens({TokenType::IDENTIFIER})) {
        return assignExpr();
    }

    return equatity();
}

AbsExpr::ptr Parser::equatity()
{
    std::initializer_list<TokenType> matchTk {TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL};
    return this->template binary_expression_reimpl<&Parser::comparsion>(matchTk);
}

AbsExpr::ptr Parser::comparsion()
{
    std::initializer_list<TokenType> matchTk {TokenType::LESS, TokenType::LESS_EQUAL, 
                                                TokenType::GREATER, TokenType::GREATER_EQUAL};
    return this->template binary_expression_reimpl<&Parser::term>(matchTk);
}

AbsExpr::ptr Parser::term()
{
    std::initializer_list<TokenType> matchTk {TokenType::PLUS, TokenType::MINUS}; 
    return this->template binary_expression_reimpl<&Parser::factor>(matchTk);
}

AbsExpr::ptr Parser::factor()
{
    std::initializer_list<TokenType> matchTk {TokenType::SLASH, TokenType::STAR}; 
    return this->template binary_expression_reimpl<&Parser::unary>(matchTk);
}
AbsExpr::ptr Parser::unary()
{
    AbsExpr::ptr subExpr;
    if (matchTokens({TokenType::MINUS, TokenType::BANG})) {
        auto op = current();
        advance();
        subExpr = primary();
        subExpr = UnaryExpr::create(op, subExpr);
    } else {
        subExpr = primary();
    }
    return subExpr;
}

AbsExpr::ptr Parser::primary()
{
    if (matchTokens({TokenType::NUMBER, TokenType::STRING, TokenType::IDENTIFIER})) {
         auto res = LiteralExpr::create(current());
         advance();
         return res;
    }

    if (matchTokens({TokenType::LEFT_BRACE})) {
        advance();
        auto expr = expression();
        consume({TokenType::RIGHT_BRACE});
        auto res = GroupExpr::create(expr);
        advance();
        return res;
    }
    bad_grammar bg("error at ");
    throw bg;
    return nullptr;
}

AbsExpr::ptr Parser::assignExpr() 
{   AbsExpr::ptr res = equatity();
    Token identifier = current();
    if (matchTokens({TokenType::EQUAL})) {
        identifier = previous();
    }
    consume({TokenType::EQUAL});
    AbsExpr::ptr expr = expression();
    return AssignExpr::create(identifier, expr);
}

AbsStmt::ptr Parser::exprStmt()
{
    AbsExpr::ptr expr = expression();
    return ExprStmt::create(expr);
}

AbsStmt::ptr Parser::printStmt()
{
    consume({TokenType::PRINT});
    AbsExpr::ptr expr = expression();
    consume({TokenType::COMMA});
    return PrintStmt::create(expr);

}

AbsStmt::ptr Parser::blockStmt()
{
    consume({TokenType::LEFT_BRACE});
    std::list<AbsStmt::ptr> stmts;
    while( !atEnd() && !matchTokens({TokenType::RIGHT_BRACE})) {
        stmts.push_back(declaration());
    }
    consume({TokenType::RIGHT_BRACE});
    return BlockStmt::create(stmts);
}

AbsStmt::ptr Parser::declaration()
{
    try {
        if (matchTokens({TokenType::VAR})) {
            return varDecl();
        }
        return statement();
    } catch (const std::exception& e) {
        synchronize();
        return nullptr;
    }
}


AbsStmt::ptr Parser::statement()
{
    AbsStmt::ptr res;
    if (matchTokens({TokenType::PRINT})) {
        res =  printStmt();
    }
    if (matchTokens({TokenType::LEFT_BRACE})) {
        res = blockStmt();
    }
    res = exprStmt();
    return StmtDecl::create(res);
}

AbsStmt::ptr Parser::varDecl()
{
    consume({TokenType::VAR});
    Token tk = current();
    AbsExpr::ptr expr;
    if (matchTokens({TokenType::EQUAL})) {
        expr = expression();
    }
    
    consume({TokenType::COMMA});
    return VarDecl::create(tk, expr);

}
