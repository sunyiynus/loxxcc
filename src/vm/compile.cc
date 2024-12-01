#include "compile.h"

void Compiler::expression()
{
    parsePrecedence(Precedence::PPREC_ASSIGNMENT);    
}


void Compiler::primary()
{

}

void Compiler::parsePrecedence(const Precedence precedence)
{
    advance();
    while (currentPrecedence() > precedence) {
        advance();
        switch (previous().token) {
            case TokenType::PLUS:
                parsePrecedence(Precedence::PPREC_TERM);
                emitByte(op_type::OP_ADD);
                break;
            case TokenType::MINUS:
                parsePrecedence(Precedence::PPREC_TERM); 
                emitByte(op_type::OP_SUBTRACT);
                break;
            case TokenType::STAR:
                parsePrecedence(Precedence::PPREC_FACTOR);
                emitByte(op_type::OP_MULTIPLY);
                break;
            case TokenType::SLASH:
                parsePrecedence(Precedence::PPREC_FACTOR);
                emitByte(op_type::OP_DIVIDE);
                break;
            default:
                return;
        }
    }
}


void Compiler::unary()
{
    TokenType tt = previous().token;

    expression();
    switch (tt)
    {
    case TokenType::MINUS : emitByte( op_type::OP_NEGATE); break;
    default:
        break;
    }

}