#ifndef PARSER_H
#define PARSER_H

#include "common.h"
#include "expression.h"
#include "stmt.h"

class Parser {
public:

    Parser(const Tokens& tk): tokensSeq(tk), curItr(tokensSeq.begin()) {}
    Parser():tokensSeq(), curItr(tokensSeq.begin()) {}
    Parser(Parser&& p) : tokensSeq(std::move(p.tokensSeq)), curItr(tokensSeq.begin()) {}
    Parser& operator=(Parser&& p)
    {
        tokensSeq = std::move(p.tokensSeq);
        curItr = tokensSeq.begin();
        return *this;
    }
public:
    const Token& current();
    const Token& previous();
    bool atEnd() const ;
    bool matchTokens(std::initializer_list<TokenType> tktypes);
    bool matchToken(const TokenType tktype);
    void advance();
    void synchronize();
    void consume(std::initializer_list<TokenType> tktypes);
    void error();

    std::vector<AbsStmt::ptr> parse();
    AbsExpr::ptr expression();
    AbsExpr::ptr equatity();
    AbsExpr::ptr comparsion();
    AbsExpr::ptr term();
    AbsExpr::ptr factor();
    AbsExpr::ptr unary();
    AbsExpr::ptr primary();
    AbsExpr::ptr assignExpr();
    AbsStmt::ptr declStmt();
    AbsStmt::ptr printStmt();
    AbsStmt::ptr exprStmt();
    AbsStmt::ptr declaration();
    AbsStmt::ptr varDecl();
    AbsStmt::ptr statement();
    AbsStmt::ptr blockStmt();
    AbsStmt::ptr ifStmt();
    AbsStmt::ptr forStmt();
    AbsStmt::ptr funcDecl();
    AbsStmt::ptr classDecl();
    AbsStmt::ptr whileStmt();
    Tokens parameter();
    std::vector<AbsExpr::ptr> arguments();
    AbsExpr::ptr call();
    AbsExpr::ptr finishCall(AbsExpr::ptr expr);

    template<AbsExpr::ptr(Parser::*call)()>
    AbsExpr::ptr binary_expression_reimpl(std::initializer_list<TokenType>& tlist) {
        auto expr = (this->*call)();
        while (matchTokens(tlist)) {
            Token op = current();
            advance();
            auto rc   = (this->*call)();
            expr = BinaryExpr::create(expr, op, rc);
        }
        return expr;
    }



private:
    Tokens tokensSeq;
    Tokens::iterator curItr;
    uint64_t itrIdx = 0;
};

#endif // PARSER_H