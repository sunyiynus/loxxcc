#ifndef COMMON_H
#define COMMON_H


#include <string>
#include <vector>
#include <cstdint>

enum class TokenType {
    // Single-charactor 
    LEFT_BRACE, RIGHT_BRACE, LEFT_PAREN, RIGHT_PAREN,
    COMMA, DOT, SEMICOM, MINUS, PLUS, STAR, SLASH, SLASH_SLASH,
    // one or more charactors 
    EQUAL, BANG, BANG_EQUAL, EQUAL_EQUAL, 
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL, RIGHT_SHIFT, LEFT_SHIFT,

    // literal
    IDENTIFIER, STRING, NUMBER,

    // keywords
    CLASS, FUNC, NILL, RETURN, PRINT, IF, ELSE, WHILE,
    CONTINUE, BREAK, VAR,
};


struct Token 
{
    Token(const std::string l, const std::string lee, const std::uint64_t ll, const TokenType ty): literal(l), lexeme(lee), line(ll), token(ty) {}
    std::string literal;
    std::string lexeme;
    std::uint64_t line;
    TokenType token;
};


namespace SingleCharactor
{
    constexpr std::string::value_type Dot = '.';
    constexpr std::string::value_type Comma = ',';
    constexpr std::string::value_type Assign = '=';
    constexpr std::string::value_type Semicon = ';';
    constexpr std::string::value_type LeftParen = '(';
    constexpr std::string::value_type RightParen = ')';
    constexpr std::string::value_type RightBrace = '}';
    constexpr std::string::value_type LeftBrace = '{';
    constexpr std::string::value_type Greater = '>';
    constexpr std::string::value_type Less = '<';
    constexpr std::string::value_type Slash = '/';
    constexpr std::string::value_type Plus = '+';
    constexpr std::string::value_type Star = '*';
    constexpr std::string::value_type Minus = '-';
    constexpr std::string::value_type Bang = '!';
    constexpr std::string::value_type NewLine = '\n';
    constexpr std::string::value_type WhiteSpace = ' ';
    constexpr std::string::value_type DoubleQuote = '"';
    constexpr std::string::value_type SingleQuote = '\'';

} // namespace SingleCharactor



using TokensType = std::vector<Token>;



#endif // COMMON_H