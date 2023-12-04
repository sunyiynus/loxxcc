#include "parser.h"
#include <functional>


void Parser::parse() {
    expression();
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
        if (tmpItr->token == tktype) {
            continue;
        } else {
            return false;
        }
    }
    return true;
}


AbsExpr::ptr Parser::expression()
{
    return equatity();
}

AbsExpr::ptr Parser::equatity()
{
    std::initializer_list<TokenType> matchTk {TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL};
    return this->template binary_expression(std::bind(&Parser::comparsion, this), matchTk);
}

AbsExpr::ptr Parser::comparsion()
{
    std::initializer_list<TokenType> matchTk {TokenType::LESS, TokenType::LESS_EQUAL, 
                                                TokenType::GREATER, TokenType::GREATER_EQUAL};
    return this->template binary_expression(std::bind(&Parser::term, this), matchTk);
}

AbsExpr::ptr Parser::term()
{
    std::initializer_list<TokenType> matchTk {TokenType::PLUS, TokenType::MINUS}; 
    return this->template binary_expression(std::bind(&Parser::factor, this), matchTk);
}

AbsExpr::ptr Parser::factor()
{
    std::initializer_list<TokenType> matchTk {TokenType::SLASH, TokenType::STAR}; 
    return this->template binary_expression(std::bind(&Parser::unary, this), matchTk);

}
AbsExpr::ptr Parser::unary()
{
    AbsExpr::ptr subExpr;
    if (matchTokens({TokenType::MINUS, TokenType::BANG})) {
        Token op = current();
        subExpr = primary();
        auto unaryExpr = UnaryExpr::create(op, subExpr);
    } else {
        subExpr = primary();
        // auto unary = LiteralExpr::create();
    }
    return subExpr;
}

AbsExpr::ptr Parser::primary()
{
    // if (matchTokens({TokenType::NUMBER, TokenType::STRING, TokenType::NILL, 
    //                 TokenType::TRUE, TokenType::FALSE}))

}
