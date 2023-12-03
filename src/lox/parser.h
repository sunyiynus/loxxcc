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

private:
    TokensType tokens;
    TokensType::iterator curItr;
};

#endif // PARSER_H