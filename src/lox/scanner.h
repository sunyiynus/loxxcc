#ifndef SCANNER_H
#define SCANNER_H

#include <functional>
#include "common.h"
#include "errors.h"

class Scanner {
public:
    Scanner() = default;
    Scanner(const std::string& s);
    const Tokens& scanTokens();

    bool atEnd() const;
    std::string::value_type current();
    void makeToken(TokenType type);
    void advanceHead();
    void advanceTail();
    void advance();
    void lineCount();
    bool forwardMatch(const char target);
    bool forwardMatch(std::function<bool(const char)> predict);
    void numbers();
    void strings();
    void identifer();
    void comments();

    void error();
    ErrorInfo genErrorInfo();


private:
    std::string src;
    std::string srcFileName;
    std::string::size_type tail;
    std::string::size_type head;
    std::uint64_t currenLine;
    Tokens tokens;
};

#endif // SCANNER_H