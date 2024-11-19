#ifndef VISITOR_H
#define VISITOR_H

#include <string>
#include <memory>
#include <limits>
#include "any.h"
#include "types.h"


template<typename DeriveT>
struct add_create_func {
public:
    static std::shared_ptr<DeriveT> create() {
        return std::make_shared<DeriveT>();
    }
};


enum class prim_type {
    Number, LongInt, String, Boolean, Callable, Nil
};

static inline bool double2bool(const number val)
{
    return (std::abs(val) > std::numeric_limits<number>::epsilon()) ? true : false;
}

struct AnyResult: public add_create_func<AnyResult> {
    AnyResult() : type(prim_type::Nil) {}
    AnyResult(const AnyResult& ) = default;
    AnyResult(AnyResult&& v) = default;
    using add_create_func<AnyResult>::create;
    using ptr = std::shared_ptr<AnyResult>;
    prim_type type;
    std::string resultStr;
    Any value;

    explicit operator std::string() {
        std::string res;
        switch (type)
        {
        case prim_type::Number:
            res = std::to_string(value.get<number>());
            break;
        case prim_type::LongInt:
            res = std::to_string(value.get<long int>());
            break;
        case prim_type::String:
            res = value.get<std::string>();
            break;
        case prim_type::Boolean:
            res = std::to_string(value.get<bool>());
            break;
        case prim_type::Callable:
            res = "Callable";
            break;
        case prim_type::Nil:
            res = "nil";
        default:
            break;
        }
        return res;
    }

    operator bool() {
        bool res = false;
        switch (type)
        {
        case prim_type::Number:
            res = double2bool(value.get<number>());
            break;
        case prim_type::LongInt:
            res = value.get<long int>();
            break;
        case prim_type::String:
            res = !value.get<std::string>().empty();
            break;
        case prim_type::Boolean:
            res = value.get<bool>();
            break;
        case prim_type::Callable:
            res = true;
            break;
        case prim_type::Nil:
            res = false;
        default:
            break;
        }
        return res;
    }
};



template <typename...Args>
class Visitor;


template <typename T>
class Visitor<T> {
public:
    virtual AnyResult::ptr visit(T* expr) = 0;
};


template <typename T, typename ... Args>
class Visitor<T, Args...>: public Visitor<Args...> {
public:
    using Visitor<Args...>::visit;
    virtual AnyResult::ptr visit(T* expr) = 0;
    
};

template <typename DeriveT, typename PT, typename VT>
class Visitable : public PT {
public:
    AnyResult::ptr accept(VT* visitor) {
        return visitor->visit(static_cast<DeriveT*>(this));
    }
};


#endif // VISITOR_H