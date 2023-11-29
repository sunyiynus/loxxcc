#ifndef VISITOR_H
#define VISITOR_H

#include <string>

struct VisitorAbsResult {
    int type;
    using ptr = std::unique_ptr<VisitorAbsResult>;
    std::string resultStr;
};


template <typename...Args>
class Visitor;


template <typename T>
class Visitor<T> {
    virtual VisitorAbsResult::ptr visit(T* expr) = 0;
};


template <typename T, typename ... Args>
class Visitor<T, Args...>: public Visitor<Args..> {
public:
    using Visitor<Args...>::visit;
    virtual VisitorAbsResult::ptr visit(T* expr) = 0;
    
};


#endif // VISITOR_H