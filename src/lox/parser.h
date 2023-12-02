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

    AbsExpr::ptr express(); 

private:
    TokensType tokens;
    TokensType::iterator curItr;
};

#endif // PARSER_H