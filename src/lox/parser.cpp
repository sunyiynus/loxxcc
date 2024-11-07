#include "parser.h"
#include <functional>
#include <list>
#include "errors.h"


AbsExpr::ptr Parser::parse() {
    std::list<AbsStmt::ptr> stmts;

    while (!atEnd()) {
        stmts.push_back(declaration());
    }
}

const Token& Parser::current()
{
    return *curItr;
}


bool Parser::atEnd() const {
    return curItr == tokens.end();
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
        return;
    }

    // error

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
{
    Token tk = current();
    consume({TokenType::EQUAL});
    AbsExpr::ptr expr = expression();
    return AssignExpr::create(tk, expr);
}


AbsStmt::ptr Parser::declStmt()
{
    Token tk = current();
    consume({TokenType::EQUAL});
    AbsExpr::ptr expr = expression();
    return DeclStmt::create(tk, expr);
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
    return PrintStmt::create(expr);

}

AbsStmt::ptr Parser::blockStmt()
{
    consume({TokenType::LEFT_BRACE});
    std::list<AbsStmt::ptr> stmts = declaration();
    consume({TokenType::RIGHT_BRACE});
    return  BlockStmt::create(stmts);
}

AbsStmt::ptr Parser::declaration()
{
    if (matchTokens({TokenType::VAR})) {
        return declStmt();
    }

    if (matchTokens({TokenType::PRINT})) {
        return printStmt();
    }

    if (matchTokens({TokenType::LEFT_BRACE})) {
        return blockStmt();
    }
    return exprStmt();

}

