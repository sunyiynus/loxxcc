#ifndef VISITOR_H
#define VISITOR_H

#include <string>
#include <memory>
#include "any.h"


template<typename DeriveT>
struct add_create_func {
public:
    static std::shared_ptr<DeriveT> create() {
        return std::make_shared<DeriveT>();
    }
};

struct VisitorAbsResult: public add_create_func<VisitorAbsResult> {
    VisitorAbsResult() = default;
    VisitorAbsResult(const VisitorAbsResult& ) = default;
    VisitorAbsResult(VisitorAbsResult&& v) = default;
    using add_create_func<VisitorAbsResult>::create;
    using ptr = std::shared_ptr<VisitorAbsResult>;
    int type;
    std::string resultStr;
    Any value;

};


template <typename...Args>
class Visitor;


template <typename T>
class Visitor<T> {
public:
    virtual VisitorAbsResult::ptr visit(T* expr) = 0;
};


template <typename T, typename ... Args>
class Visitor<T, Args...>: public Visitor<Args...> {
public:
    using Visitor<Args...>::visit;
    virtual VisitorAbsResult::ptr visit(T* expr) = 0;
    
};

template <typename DeriveT, typename PT, typename VT>
class Visitable : public PT {
public:
    VisitorAbsResult::ptr accept(VT* visitor) {
        return visitor->visit(static_cast<DeriveT*>(this));
    }
};


#endif // VISITOR_H