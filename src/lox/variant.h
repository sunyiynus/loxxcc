#ifndef VARIANT_H
#define VARIANT_H
#include "mp.h"

template <typename ...Args>
class Variant {
    static_assert(is_unique_args<Args ...>::value == true);
public: 
    Variant() = default;
};


#endif // VARIANT_H