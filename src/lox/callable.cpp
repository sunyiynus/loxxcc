#include "callable.h"
#include "stmt.h"
#include "interpreter.h"


AnyResult::ptr LoxFunction::call(Interpreter* ptr , std::vector<AnyResult::ptr> args)
{
    auto environment = std::make_shared<Environment>(ptr->globalEnvironment());
    for (int i = 0; i < declaration->parameter.size(); ++i) {
        environment->define(declaration->parameter[i].lexeme,  args[i]);
    }

    ptr->execute(declaration->stmts, environment);
}

uint64_t LoxFunction::arity() const {
    return declaration->parameter.size();
}