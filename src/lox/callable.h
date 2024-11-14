#ifndef CALLABLE_H
#define CALLABLE_H

#include "common.h"
#include "visitor.h"
#include "interpreter.h"

class LoxCallable {
public:
    virtual AnyResult::ptr call(Interpreter* ptr , std::vector<AnyResult::ptr> args) = 0;
};


class LoxFunction : public LoxCallable {
public:
    LoxFunction() = default;
    AnyResult::ptr call(Interpreter* ptr , std::vector<AnyResult::ptr> args) override;

private:
    Tokens parameter;
};


#endif // CALLABLE_H