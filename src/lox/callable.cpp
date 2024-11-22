#include "callable.h"
#include "stmt.h"
#include "interpreter.h"


AnyResult::ptr LoxFunction::call(Interpreter* ptr , std::vector<AnyResult::ptr> args)
{
    auto environment = std::make_shared<Environment>(ptr->globalEnvironment());
    for (int i = 0; i < declaration->parameter.size(); ++i) {
        environment->define(declaration->parameter[i].lexeme,  args[i]);
    }

    auto res = ptr->execute(declaration->stmts, environment);
    return res;
}

uint64_t LoxFunction::arity() const {
    return declaration->parameter.size();
}

LoxFunction::operator std::string()
{
    return declaration->funcName.lexeme;
}