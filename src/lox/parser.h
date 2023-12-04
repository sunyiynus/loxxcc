#ifndef PARSER_H
#define PARSER_H

#include "common.h"
#include "expression.h"

class Parser {
public:

    Parser(const TokensType& tk): tokens(tk) {}

    Parser():tokens(), curItr(tokens.begin()) {}
    void parse();
    const Token& current();
    bool atEnd() const ;
    bool matchTokens(std::initializer_list<TokenType> tktypes);

    AbsExpr::ptr expression();
    AbsExpr::ptr equatity();
    AbsExpr::ptr comparsion();
    AbsExpr::ptr term();
    AbsExpr::ptr factor();
    AbsExpr::ptr unary();
    AbsExpr::ptr primary();

    template<typename FT>
    AbsExpr::ptr binary_expression(FT call, std::initializer_list<TokenType>& tlist) {
        auto expr = call();
        while (matchTokens(tlist)) {
            Token op      = current();
            auto  rc      = call();
            expr = BinaryExpr::create(expr, op, rc);
        }
        return expr;
    }

    template<AbsExpr::ptr(Parser::*call)()>
    AbsExpr::ptr binary_expression_reimpl(std::initializer_list<TokenType>& tlist) {
        auto expr = (this->*call)();
        while (matchTokens(tlist)) {
            Token op      = current();
            auto  rc      = (this->*call)();
            expr = BinaryExpr::create(expr, op, rc);
        }
        return expr;
    }



private:
    TokensType tokens;
    TokensType::iterator curItr;
};

#endif // PARSER_H