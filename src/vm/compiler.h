#ifndef COMPILE_H
#define COMPILE_H

#include <vector>
#include <iostream>
#include <cstdint>

#include "chunk.h"
#include "common.h"


class Compiler
{
private:
    Tokens tks;
    chunk::ptr chuk;
    Tokens::iterator currentItr;
    Tokens::iterator preItr;
public:
    Compiler(Tokens&& tokens) : chuk(std::make_shared<chunk>()), tks(std::move(tokens)) { }

    bool end(void) {
        return currentItr == tks.end();
    }

    void compile(void) {
        currentItr = tks.begin();
        preItr = tks.begin();

        while (!end()) {
            parse();
        }

    }

    void advance() {
        currentItr++;
    }

    void emitByteCode();
    void emitBytes(const value_type value) {

    }

};


#endif // COMPILE_H