#ifndef COMMON_H
#define COMMON_H


#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <cstdint>

enum class TokenType {
    // Single-charactor 
    LEFT_BRACE, RIGHT_BRACE, LEFT_PAREN, RIGHT_PAREN,PERCENT,
    COMMA, DOT, SEMICOM, MINUS, PLUS, STAR, SLASH, SLASH_SLASH,
    // one or more charactors 
    EQUAL, BANG, BANG_EQUAL, EQUAL_EQUAL, 
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL, RIGHT_SHIFT, LEFT_SHIFT,

    // literal
    IDENTIFIER, STRING, NUMBER,

    // keywords
    CLASS, FUNC, NILL, RETURN, PRINT, IF, ELSE, WHILE,
    CONTINUE, BREAK, VAR, THIS,
    F_EOF, TRUE, FALSE,
};


struct Token 
{
    // Token(Token&& tk) {
    //     literal = std::move(tk.lexeme);
    //     lexeme = std::move(tk.lexeme);
    //     line = tk.line;
    //     token = tk.token;
    // }
    Token() = default;
    Token(const Token& ) = default;
    Token(const std::string l, const std::string lee, const std::uint64_t ll, const TokenType ty): literal(l), lexeme(lee), line(ll), token(ty) {}
    Token& operator=(Token&& tk) {
        literal = std::move(tk.lexeme);
        lexeme = std::move(tk.lexeme);
        line = tk.line;
        token = tk.token;
        return *this;
    }
    Token& operator=(const Token&) = default;
    std::string literal;
    std::string lexeme;
    std::uint64_t line;
    TokenType token;

    explicit operator std::string() const {
        std::string res = std::to_string(line) + ": " + lexeme;
        return res;
    }
};


namespace SingleCharactor
{
    constexpr std::string::value_type Dot         = '.';
    constexpr std::string::value_type Comma       = ',';
    constexpr std::string::value_type Assign      = '=';
    constexpr std::string::value_type Semicon     = ';';
    constexpr std::string::value_type LeftParen   = '(';
    constexpr std::string::value_type RightParen  = ')';
    constexpr std::string::value_type RightBrace  = '}';
    constexpr std::string::value_type LeftBrace   = '{';
    constexpr std::string::value_type Greater     = '>';
    constexpr std::string::value_type Less        = '<';
    constexpr std::string::value_type Slash       = '/';
    constexpr std::string::value_type Plus        = '+';
    constexpr std::string::value_type Star        = '*';
    constexpr std::string::value_type Minus       = '-';
    constexpr std::string::value_type Bang        = '!';
    constexpr std::string::value_type NewLine     = '\n';
    constexpr std::string::value_type WhiteSpace  = ' ';
    constexpr std::string::value_type DoubleQuote = '"';
    constexpr std::string::value_type SingleQuote = '\'';
    constexpr std::string::value_type Percent     = '%';

} // namespace SingleCharactor

namespace Keywords
{
    const std::string Class    = "class";
    const std::string Func     = "fn";
    const std::string Nil      = "nil";
    const std::string Return   = "return";
    const std::string Print    = "print";
    const std::string If       = "if";
    const std::string Else     = "else";
    const std::string While    = "while";
    const std::string Continue = "continue";
    const std::string Break    = "break";
    const std::string Var      = "var";
    const std::string This     = "this";
    const std::string True     = "true";
    const std::string False    = "false";

    const std::map<std::string, TokenType> Table {  {Class,     TokenType::CLASS},
                                                    {Func,      TokenType::FUNC},
                                                    {Nil,       TokenType::NILL},
                                                    {Return,    TokenType::RETURN},
                                                    {Print,     TokenType::PRINT},
                                                    {If,        TokenType::IF},
                                                    {Else,      TokenType::ELSE},
                                                    {While,     TokenType::WHILE},
                                                    {Continue,  TokenType::CONTINUE},
                                                    {Break,     TokenType::BREAK},
                                                    {Var,       TokenType::VAR},
                                                    {This,      TokenType::THIS},
                                                    {True,      TokenType::TRUE},
                                                    {False,     TokenType::FALSE},
                                                    };

} // namespace Keywords



using TokensType = std::vector<Token>;

std::ostream& operator<<(std::ostream& outstream, const std::vector<Token>& tokens);




#endif // COMMON_H