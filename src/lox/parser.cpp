#include "parser.h"



void Parser::parse() {
    if ()
    parse();
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
        if (*tmpItr->token == tktype) {
            continue;
        } else {
            return false;
        }
    }
    return true;
}


AbsExpr::ptr Parser::expression()
{
    while (equatity()) {

    }

}
AbsExpr::ptr Parser::equatity()
{
    while ( true) {
        auto lc = comparsion();
        decltype(lc) rc;
        Token op;
        if (matchTokens({TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL})) {
            op = current();
            rc = comparsion();
        }
        auto binExpr = BinaryExpr::create(lc, Token(), rc);
    }

}

AbsExpr::ptr Parser::comparsion()
{
    while(true) {
        auto lc = term();
        decltype(lc) rc;
        Token op;
        std::initializer_list<TokenType> matchTk {TokenType::LESS, TokenType::LESS_EQUAL, 
                                                TokenType::GREATER, TokenType::GREATER_EQUAL};
        if (matchTokens(matchTk)) {
            op = current();
            rc = term();
        }
        auto binExpr = BinaryExpr::create(lc, Token(), rc);
    }

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
    while(true) {
        auto lc = unary();
        decltype(lc) rc;
        Token op;
        std::initializer_list<TokenType> matchTk {TokenType::SLASH, TokenType::STAR}; 
        if (matchTokens(matchTk)) {
            op = current();
            rc = unary();
        }
        auto binExpr = BinaryExpr::create(lc, Token(), rc);
    }

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
        auto unary = LiteralExpr::create();
    }
}
AbsExpr::ptr Parser::primary()
{
    if (matchTokens({TokenType::NUMBER, TokenType::STRING, TokenType::NILL, 
                    TokenType::TRUE, TokenType::FALSE}))

}
