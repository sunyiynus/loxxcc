#include "scanner.h"


Scanner::Scanner(const std::string& s): src(s), head(0), tail(0) {}


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
                advanceHead();
                makeToken(TokenType::EQUAL_EQUAL);
            } else {
                makeToken(TokenType::EQUAL);
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
                advanceHead();
                makeToken(TokenType::GREATER_EQUAL);
            } else if (forwardMatch(SingleCharactor::Greater)) {
                advanceHead();
                makeToken(TokenType::RIGHT_SHIFT);
            } else {
                makeToken(TokenType::GREATER);
            }
            break;
        case SingleCharactor::Less:
            if (forwardMatch(SingleCharactor::Assign)) {
                advanceHead();
                makeToken(TokenType::LESS_EQUAL);
            } else if (forwardMatch(SingleCharactor::Less)) {
                advanceHead();
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
                advanceHead();
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
                advanceHead();
                numbers();
                makeToken(TokenType::NUMBER);
            } else {
                makeToken(TokenType::MINUS);
            }
            break;
        case SingleCharactor::WhiteSpace:
            advanceHead();
            advanceTail();
            break;
        case SingleCharactor::DoubleQuote:
            strings();
            break;
        default:
            if (std::isdigit(current())) {
                numbers();
            } else if (std::isalpha(current())) {
                identifer();
            } else {
                advanceHead();
            }
            break;
        }
    }

    return tokens;
}


bool Scanner::atEnd() const
{
    return !(tail < src.size());
}


std::string::value_type Scanner::current()
{
    return src[head];
}

void Scanner::makeToken(TokenType type)
{
    advanceHead();
    std::string::size_type cnt = head - tail;
    tokens.emplace_back(src.substr(tail, cnt), src.substr(tail,cnt), currenLine, type);
    advance();
}

void Scanner::advance()
{
    tail = head;
}

void Scanner::advanceHead()
{
    head++;
}

void Scanner::advanceTail()
{
    tail++;
}

void Scanner::lineCount()
{
    currenLine++;
}


bool Scanner::forwardMatch(const char target)
{
    auto tmp = tail + 1;
    return (src[tmp] == target);
}

bool Scanner::forwardMatch(std::function<bool(const char)> predict)
{
    auto tmp = head + 1;
    return predict(src[tmp]);
}

void Scanner::numbers()
{
    int dotCnt = 1;
    auto isDot = [](char c)->bool { return c == SingleCharactor::Dot;};
    while (std::isdigit(current()) || isDot(current())) {
        if (dotCnt < 0) {
            // error
        }
        if (isDot(current())) {
            dotCnt--;
        }
        advanceHead();
    }
    std::string::size_type cnt = head - tail;
    tokens.emplace_back(src.substr(tail, cnt), src.substr(tail,cnt), currenLine, TokenType::NUMBER);
    advance();
}

void Scanner::strings()
{
    advanceTail();
    advanceHead();
    while (std::isprint(current())) {
        if (current() == SingleCharactor::DoubleQuote) {
            break;
        } else if (current() == SingleCharactor::NewLine) {
            error();
        } else {
            advanceHead();
        }
    }

    std::string::size_type cnt = head - tail;
    tokens.emplace_back(src.substr(tail, cnt), src.substr(tail,cnt), currenLine, TokenType::STRING);
    advanceHead();
    advance();
}

void Scanner::identifer()
{
    advanceHead();
    auto isIdentify = [](const char c) -> bool { return std::isalpha(c) || c == '_' || std::isdigit(c);};
    while (isIdentify(current())) {
        advanceHead();
    }
    std::string::size_type cnt = head - tail;
    tokens.emplace_back(src.substr(tail, cnt), src.substr(tail,cnt), currenLine, TokenType::IDENTIFIER);
    advance();
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


