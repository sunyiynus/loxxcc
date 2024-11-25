#ifndef DEBUG_H
#define DEBUG_H

#include <vector>
#include <iostream>
#include <cstdint>

#include "chunk.h"

class Debuger
{
public:
    Debuger() : oss(std::cout), printedHeader(false) {}
private:
    std::reference_wrapper<std::ostream> oss;
    bool printedHeader;
public:
    void printHeader() {
        if (!printedHeader) {
            oss.get() << "++++++ chunk info ++++++\n";
            printedHeader = true;
        }
    }

    void printReturnOp() {
        oss.get() << "return " << '\n';
    }

    void disassembly(const bytecode_type& op) {
        printHeader();
        switch (static_cast<op_type>(op[BYTECODE_OP_POS]))
        {
        case op_type::OP_RETURN :
            printReturnOp();
            break;
        
        default:
            break;
        }
    }
};


#endif // DEBUG_H