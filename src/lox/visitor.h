#ifndef VISITOR_H
#define VISITOR_H

#include <string>
#include <memory>


template<typename DeriveT>
struct add_create_func {
public:
    static std::shared_ptr<DeriveT> create() {
        return std::shared_ptr<DeriveT>();
    }
};

struct VisitorAbsResult: public add_create_func<VisitorAbsResult> {
    VisitorAbsResult() = default;
    VisitorAbsResult(const VisitorAbsResult& ) = default;
    VisitorAbsResult(VisitorAbsResult&& v) = default;
    using add_create_func<VisitorAbsResult>::create;
    int type;
    using ptr = std::shared_ptr<VisitorAbsResult>;
    std::string resultStr;
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


#endif // VISITOR_H