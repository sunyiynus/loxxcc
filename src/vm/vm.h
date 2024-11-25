//
// Created by Konstantin Gredeskoul on 5/14/17.
//

#ifndef CMAKE_VM_H
#define CMAKE_VM_H

static const char *const VM_MESSAGE = "Virtual Machine For Lox!";

#include <iostream>
#include <stdexcept>
#include <stack>
#include "any.h"
#include "chunk.h"



class Vm
{
public:
    Vm() : pc(0) {}
private:
    chunk chunks;
    uint64_t pc;
    std::stack<value_type> stack;
public:
    void addChunk(chunk&& chk) {
        chunks= std::move(chk);
    }

    void interpret(const bytecode_type& code)
    {
        switch (static_cast<op_type>(code[BYTECODE_OP_POS]))
        {
        case op_type::OP_RETURN :
            break;
        case op_type::OP_CONSTANT :
            stack.push(chunks.constValue[code[BYTECODE_OPRAND_POS]]);
            break;
        case op_type::OP_NEGATE :
            // stack.push( - stack.pop());
            break;
        case op_type::OP_ADD :
            // stack.push( - stack.pop());
            break;
        default:
            break;
        }
    }
    void run() {
#ifdef DEBUG_TRACE_EXECUTION
#endif // DEBUG_TRACE_EXECUTION
        while (pc < chunks.ops.size()) {
            interpret(chunks.readByteCode(pc));
        }
    }

};



#endif //CMAKE_DIVISION_H
