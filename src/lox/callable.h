#ifndef CALLABLE_H
#define CALLABLE_H

#include "common.h"

class LoxCallable {
public:
};


class LoxFunction : public LoxCallable {

private:
    Tokens parameter;
};


#endif // CALLABLE_H