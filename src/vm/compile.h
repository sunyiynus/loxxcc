#ifndef COMPILE_H
#define COMPILE_H

#include <vector>
#include <iostream>
#include <cstdint>

#include "chunk.h"
#include "common.h"


class Compiler
{
public:
    enum class Precedence {
        PPREC_NONE,
        PPREC_ASSIGNMENT,  // =
        PPREC_OR,         // or
        PPREC_AND,        // and
        PPREC_EQUALITY,   // == !=
        PPREC_COMPARISON, // < > <= >=
        PPREC_TERM,       // + -
        PPREC_FACTOR,     // * /
        PPREC_UNARY,      // ! -
        PPREC_CALL,       // . ()
        PPREC_PRIMARY
    };
private:
    Tokens tks;
    chunk::ptr chuk;
    Tokens::iterator currentItr;
    Tokens::iterator preItr;
    bool panicMode = false;
    bool hadError = false;
public:
    Compiler(Tokens&& tokens) : chuk(std::make_shared<chunk>()), tks(std::move(tokens)) { }
    Compiler() : currentItr(tks.begin()), preItr(currentItr) {}
public:

    bool end(void) {
        return currentItr == tks.end();
    }

    bool compile(void) {
        currentItr = tks.begin();
        preItr = tks.begin();

        while (!end()) {
            expression();
        }
        endCompile();
        return !hadError;

    }

    void endCompile() {
        emitByte(op_type::OP_RETURN);
    }

    void advance() {
        currentItr++;
    }

    const Token& current() {
        return *currentItr;
    }

    const Token& previous() {
        auto tmp = currentItr;
        tmp--;
        return *tmp;
    }

    void consume(const TokenType tt, const std::string& msg) {
        if (current().token == tt) {
            advance();
            return;
        }
        errorAtCurrent(msg);
    }

    void errorAtCurrent(const std::string& msg) {
        errorAt(*currentItr, msg);
    }

    void errorAt(const Token& tk, const std::string& msg) {
        if (panicMode) return;
        panicMode = true;
        std::cerr << "[line " << tk.line << "] Error: " << msg << " \n";
    }

    const Precedence currentPrecedence() {
        switch (current().token) {
            case TokenType::MINUS:
            case TokenType::PLUS:
                return Precedence::PPREC_TERM;
            case TokenType::SLASH:
            case TokenType::STAR:
                return Precedence::PPREC_FACTOR;
            case TokenType::BANG_EQUAL:
            case TokenType::EQUAL_EQUAL:
                return Precedence::PPREC_EQUALITY;
            case TokenType::GREATER:
            case TokenType::GREATER_EQUAL:
            case TokenType::LESS:
            case TokenType::LESS_EQUAL:
                return Precedence::PPREC_COMPARISON;
            case TokenType::AND:
                return Precedence::PPREC_AND;
            case TokenType::OR:
                return Precedence::PPREC_OR;
            default:
                return Precedence::PPREC_NONE;
        }
    }

    void emitByte(const op_type op, const uint8_t val)
    {
        chuk->appendOp(op, val, (*currentItr).line);
    }
    
    void emitByte(const op_type code) {
        chuk->appendOp(code, (*currentItr).line);
    }


    void expression(void);
    void parsePrecedence(const Precedence precedence);
    void grouping(void);
    void binary(void);
    void number(void);
    void unary(void);

};


#endif // COMPILE_H