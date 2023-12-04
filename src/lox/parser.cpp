#include "parser.h"



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

}
AbsExpr::ptr Parser::equatity()
{
    auto expr = comparsion();
    while (matchTokens({TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL})) {
        Token op      = current();
        auto  rc      = comparsion();
        expr = BinaryExpr::create(expr, Token(), rc);
    }
    return expr;
}

AbsExpr::ptr Parser::comparsion()
{
    auto lc = term();
    std::initializer_list<TokenType> matchTk {TokenType::LESS, TokenType::LESS_EQUAL, 
                                                TokenType::GREATER, TokenType::GREATER_EQUAL};
    while(matchTokens(matchTk)) {
        Token op = current();
        auto rc = term();
        lc = BinaryExpr::create(lc, Token(), rc);
    }
    return lc;

}
AbsExpr::ptr Parser::term()
{
    while(true) {
        auto lc = factor();
        decltype(lc) rc;
        Token op;
        std::initializer_list<TokenType> matchTk {TokenType::PLUS, TokenType::MINUS}; 
        if (matchTokens(matchTk)) {
            op = current();
            rc = factor();
        }
        auto binExpr = BinaryExpr::create(lc, Token(), rc);
    }

}
AbsExpr::ptr Parser::factor()
{
    std::initializer_list<TokenType> matchTk {TokenType::SLASH, TokenType::STAR}; 
    return this->template binary_expression<&unary>(unary, matchTk);

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
