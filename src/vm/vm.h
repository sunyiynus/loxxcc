//
// Created by Konstantin Gredeskoul on 5/14/17.
//

#ifndef CMAKE_VM_H
#define CMAKE_VM_H

static const char *const VM_MESSAGE = "Virtual Machine For Lox!";

#include <iostream>
#include <stdexcept>


#include "chunk.h"


class Vm
{
private:
    chunk chunks;
public:
    void run() {
        while (chunks) {
            switch (chunks.readNextOp()[0])
            {
            case op_type::OP_RETURN :
                /* code */
                break;
            
            default:
                break;
            }
        }
    }

};



#endif //CMAKE_DIVISION_H
