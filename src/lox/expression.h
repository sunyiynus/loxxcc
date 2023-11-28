#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <memory>
#include <string>

struct VisitorAbsResult {
    int type;
    using ptr = std::unique_ptr<VisitorAbsResult>;
    std::string resultStr;
};


class AbsExpr;

class AbsVisitor {
public:
    virtual VisitorAbsResult::ptr visit(AbsExpr* expr) = 0;
};


template <typename...Args>
class Visitor;


template <typename T>
class Visitor<T> {
    VisitorAbsResult::ptr visit(T* expr) override {
        return expr.accept(this);
    }
};


template <typename T, typename ... Args>
class Visitor<T, Args...> {
public:
    using Visitor<Args...>::visit();
    VisitorAbsResult::ptr visit(T* expr) override {
        return expr.accept(this);
    }
    
};


class BinaryExpr;
class UaryExpr;

using ExprVisitor  = Visitor<BinaryExpr, UaryExpr>;








class AbsExpr {
public:
    virtual VisitorAbsResult::ptr accept(ExprVisitor* visitor) = 0;
private:
};




template <typename DeriveT>
class Visitable : public AbsExpr {
public:
    VisitorAbsResult::ptr accept(ExprVisitor* visitor) {
        return visitor->visit(static_cast<DeriveT*>(this));
    }
};


class BinaryExpr : public Visitable<BinaryExpr> {
public:

}; 







#endif // EXPRESSION_H