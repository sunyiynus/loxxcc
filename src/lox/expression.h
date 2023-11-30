#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <memory>
#include <string>
#include "common.h"
#include "visitor.h"


class BinaryExpr;
class UnaryExpr;
class GroupExpr;
class LiteralExpr;

using ExprVisitor  = Visitor<BinaryExpr, UnaryExpr, GroupExpr, LiteralExpr>;



class AbsExpr {
public:
    using ptr = std::shared_ptr<AbsExpr>;
    virtual VisitorAbsResult::ptr accept(ExprVisitor* visitor) = 0;
private:
};




template <typename DeriveT>
class VisitableExpr : public AbsExpr {
public:
    VisitorAbsResult::ptr accept(ExprVisitor* visitor) {
        return visitor->visit(static_cast<DeriveT*>(this));
    }
};

template<typename DeriveT>
struct add_ptr_typedef {
    using ptr = std::shared_ptr<DeriveT>;
};

class BinaryExpr : public VisitableExpr<BinaryExpr> {
public:
    BinaryExpr() = default;
    AbsExpr::ptr lOperand;
    Token op;
    AbsExpr::ptr rOperand;
}; 

class UnaryExpr : public VisitableExpr<UnaryExpr> {
public:

    Token op;
    AbsExpr::ptr rOperand;

}; 

class GroupExpr : public VisitableExpr<GroupExpr> {
public:

    AbsExpr::ptr subExpr;
}; 


class LiteralExpr : public VisitableExpr<LiteralExpr> {
public:
    LiteralExpr() = default;
    Token literal;
}; 






#endif // EXPRESSION_H