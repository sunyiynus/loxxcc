#ifndef CALLABLE_H
#define CALLABLE_H

#include "common.h"
#include "visitor.h"
#include "interpreter.h"

class LoxCallable {
public:
    virtual AnyResult::ptr call(Interpreter* ptr , std::vector<AnyResult::ptr> args) = 0;
    virtual uint64_t arity() const;
    virtual operator std::string();
};


class LoxFunction : public LoxCallable {
public:
    LoxFunction() = default;
    LoxFunction(LoxFunction&& lf) {
        declaration = std::move(lf.declaration);
    }
    LoxFunction(FuncDecl::ptr ast) : declaration(ast) {}
    AnyResult::ptr call(Interpreter* ptr , std::vector<AnyResult::ptr> args) override;
    uint64_t arity() const override;
    operator std::string() override;

private:
    FuncDecl::ptr declaration;
};


#endif // CALLABLE_H