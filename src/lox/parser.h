#ifndef PARSER_H
#define PARSER_H

#include "common.h"
#include "expression.h"

class Parser {
public:

    Parser(const TokensType& tk): tokens(tk), curItr(tokens.begin()) {}

    Parser():tokens(), curItr(tokens.begin()) {}
    AbsExpr::ptr parse();
    const Token& current();
    bool atEnd() const ;
    bool matchTokens(std::initializer_list<TokenType> tktypes);
    void advance();
    void synchronize();
    void consume(std::initializer_list<TokenType> tktypes);
    void error();

    AbsExpr::ptr expression();
    AbsExpr::ptr equatity();
    AbsExpr::ptr comparsion();
    AbsExpr::ptr term();
    AbsExpr::ptr factor();
    AbsExpr::ptr unary();
    AbsExpr::ptr primary();

    template<AbsExpr::ptr(Parser::*call)()>
    AbsExpr::ptr binary_expression_reimpl(std::initializer_list<TokenType>& tlist) {
        auto expr = (this->*call)();
        while (matchTokens(tlist)) {
            Token op = current();
            advance();
            auto rc   = (this->*call)();
            expr = BinaryExpr::create(expr, op, rc);
        }
                                // advance();
        return expr;
    }



private:
    TokensType tokens;
    TokensType::iterator curItr;
};

#endif // PARSER_H