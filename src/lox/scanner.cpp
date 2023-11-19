#include "scanner.h"


Scanner::Scanner(const std::string& s): src(s), begin(0), end(0) {}


const TokensType& Scanner::scanTokens()
{

    if (src.empty()) {
        return tokens;
    }

    while (!atEnd()) {
        switch (current())
        {
        case SingleCharactor::Dot:
            makeToken(TokenType::DOT);
            break;
        case SingleCharactor::Assign:
            if (forwardMatch(SingleCharactor::Assign)) {
                begin++;
                makeToken(TokenType::EQUAL);
            } else {
                makeToken(TokenType::DOT);
            }
            break;
        case SingleCharactor::Comma:
            makeToken(TokenType::COMMA);
            break;
        case SingleCharactor::Semicon:
            makeToken(TokenType::SEMICOM);
            break;
        case SingleCharactor::LeftBrace:
            makeToken(TokenType::LEFT_BRACE);
            break;
        case SingleCharactor::RightBrace:
            makeToken(TokenType::RIGHT_BRACE);
            break;
        case SingleCharactor::RightParen:
            makeToken(TokenType::RIGHT_PAREN);
            break;
        case SingleCharactor::LeftParen:
            makeToken(TokenType::LEFT_PAREN);
            break;
        case SingleCharactor::Greater:
            if (forwardMatch(SingleCharactor::Assign)) {
                makeToken(TokenType::GREATER_EQUAL);
            } else if (forwardMatch(SingleCharactor::Greater)) {
                makeToken(TokenType::RIGHT_SHIFT);
            } else {
                makeToken(TokenType::GREATER);
            }
            break;
        case SingleCharactor::Less:
            if (forwardMatch(SingleCharactor::Assign)) {
                makeToken(TokenType::LESS_EQUAL);
            } else if (forwardMatch(SingleCharactor::Less)) {
                makeToken(TokenType::LEFT_SHIFT);
            } else {
                makeToken(TokenType::LESS);
            }
            break;
        case SingleCharactor::Slash:
            makeToken(TokenType::SLASH);
            break;
        case SingleCharactor::Plus:
            makeToken(TokenType::PLUS);
            break;
        case SingleCharactor::Star:
            makeToken(TokenType::STAR);
            break;
        case SingleCharactor::Bang:
            if (forwardMatch(SingleCharactor::Assign)) {
                makeToken(TokenType::BANG_EQUAL);
            } else {
                makeToken(TokenType::BANG);
            }
            break;
        case SingleCharactor::NewLine:
            lineCount();
            advance();
            break;
        case SingleCharactor::Minus:
            if (forwardMatch([](const char c)->bool{ return std::isdigit(c);})) {
                begin++;
                numbers();
                makeToken(TokenType::NUMBER);
            } else {
                makeToken(TokenType::MINUS);
            }
            break;
        case SingleCharactor::WhiteSpace:
            advance();
            break;
        case SingleCharactor::DoubleQuote:
            strings();
            makeToken(TokenType::STRING);
            break;
        default:
            break;
        }
    }

    return tokens;
}


bool Scanner::atEnd() const
{
    return !(begin < src.size());
}


std::string::value_type Scanner::current()
{
    return src[begin];
}

void Scanner::makeToken(TokenType type)
{
    begin++;
    tokens.emplace_back(src.substr(end, begin), src.substr(end,begin), currenLine, type);
    advance();
}

void Scanner::advance()
{
    end = begin,
    begin++;
}

void Scanner::lineCount()
{
    currenLine++;
}


bool Scanner::forwardMatch(const char target)
{
    auto tmp = begin + 1;
    return (src[tmp] == target);
}

bool Scanner::forwardMatch(std::function<bool(const char)> predict)
{
    auto tmp = begin + 1;
    return predict(src[tmp]);
}

void Scanner::numbers()
{
    while (std::isdigit(current())) {
        begin++;
    }
}

void Scanner::strings()
{
    begin++;
    while (std::isprint(current())) {
        if (current() == SingleCharactor::DoubleQuote) {

        } else if (current() == SingleCharactor::NewLine) {
            error();
        }
    }
}

void Scanner::error()
{
    Error::lexingError(genErrorInfo());
}

ErrorInfo Scanner::genErrorInfo()
{
    ErrorInfo info;
    info.errorMsg = ""; // 错误信息 不知道想显示啥？
    info.lineText = "";
    info.lineNo = currenLine;
    info.fileName = srcFileName;
    return info;
}


