#include "compile.h"
#include <string>

void Compiler::expression()
{
    parsePrecedence(Precedence::PPREC_ASSIGNMENT);    
}


void Compiler::number()
{
    value_type value = std::stod(current().lexeme);
    emitByte(op_type::OP_CONSTANT, chuk->storeValue(value));
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

void Compiler::grouping()
{
    expression();
    consume(TokenType::RIGHT_PAREN, "Expected ')' after expression.");
}

void Compiler::binary()
{
    TokenType tt = previous().token;

    parsePrecedence(static_cast<Precedence>(static_cast<int>(currentPrecedence()) + 1));

    switch (tt) {
        case TokenType::PLUS:
            emitByte(op_type::OP_ADD);
            break;
        case TokenType::MINUS:
            emitByte(op_type::OP_SUBTRACT); 
            break;
        case TokenType::STAR:
            emitByte(op_type::OP_MULTIPLY);
            break;
        case TokenType::SLASH:
            emitByte(op_type::OP_DIVIDE);
            break;
        default:
            return;
    }
}



void Compiler::unary()
{
    TokenType tt = previous().token;

    parsePrecedence(Precedence::PPREC_UNARY);
    switch (tt)
    {
    case TokenType::MINUS : emitByte( op_type::OP_NEGATE); break;
    default:
        break;
    }

}