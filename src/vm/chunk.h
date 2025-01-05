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
    void appendOp(const bytecode_type& op, const uint64_t ln = 0) {
        ops.emplace_back(op);
        lines.push_back(ln);
    }

    void appendOp(const op_type op, const uint64_t ln = 0)
    {
        bytecode_type tmpCode = {static_cast<uint8_t>(op), 0};
        appendOp(tmpCode, ln);
    }

    void appendOp(const op_type op, const uint8_t value, const uint64_t ln = 0)
    {
        bytecode_type tmpCode = {static_cast<uint8_t>(op), value};
        appendOp(tmpCode, ln);
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

    uint8_t storeValue(const value_type val) {
        constValue.push_back(val);
        return constValue.size() - 1;
    }

public:
    using ptr = std::shared_ptr<chunk>;
};



#endif // CHUNK_H