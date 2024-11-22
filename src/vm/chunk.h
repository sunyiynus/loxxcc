#ifndef CHUNK_H
#define CHUNK_H

#include <vector>
#include <cstdint>
#include <array>
#include <any.h>

constexpr uint64_t BYTECODE_LEN = 2;

enum class op_type {
    OP_CONSTANT,
    OP_RETURN,
};

using bytecode_type = std::array<uint8_t, BYTECODE_LEN>;

struct chunk {

    std::vector<uint64_t> lines;
    std::vector<bytecode_type> ops;
    std::vector<Any> constValue;
private:
    std::vector<bytecode_type>::iterator pc;
public:
    chunk(): pc (ops.begin()) {}
public:
    void appendOp(const bytecode_type& op) {
        ops.emplace_back(op);
    }

    const bytecode_type& readNextOp() {
        
    }

    operator bool() {
        return pc != ops.end();
    }
};


#endif // CHUNK_H