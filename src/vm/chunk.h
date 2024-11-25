#ifndef CHUNK_H
#define CHUNK_H

#include <vector>
#include <cstdint>
#include <array>
#include <any.h>

constexpr uint64_t BYTECODE_LEN = 2;
constexpr uint64_t BYTECODE_OP_POS = 0;
constexpr uint64_t BYTECODE_OPRAND_POS = 1;

enum class op_type {
    OP_CONSTANT,
    OP_NEGATE,
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_RETURN,
};

using value_type = double;

using bytecode_type = std::array<uint8_t, BYTECODE_LEN>;


struct chunk {
    std::string fileName;
    std::vector<uint64_t> lines;
    std::vector<bytecode_type> ops;
    std::vector<value_type> constValue;
private:
    std::vector<bytecode_type>::iterator pc;
public:
    chunk(): pc (ops.begin()) {}
public:
    void appendOp(const bytecode_type& op) {
        ops.emplace_back(op);
    }
    void appendOp(const uint8_t code[BYTECODE_LEN])
    {
        bytecode_type tmpCode = {code[BYTECODE_OP_POS], code[BYTECODE_OPRAND_POS]};
        appendOp(tmpCode);
    }

    const bytecode_type& readByteCode(const size_t  pos) {
        return ops[pos];
    }

    const uint8_t readOp(const size_t pos) {
        return ops[pos][BYTECODE_OP_POS];
    }

    const uint8_t readOprand(const size_t pos) {
        return ops[pos][BYTECODE_OPRAND_POS];
    }

public:
    using ptr = std::shared_ptr<chunk>;
};



#endif // CHUNK_H