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
class Visitable : public AbsExpr {
public:
    VisitorAbsResult::ptr accept(ExprVisitor* visitor) {
        return visitor->visit(static_cast<DeriveT*>(this));
    }
};

template<typename DeriveT>
struct add_ptr_typedef {
    using ptr = std::shared_ptr<DeriveT>;
};

class BinaryExpr : public Visitable<BinaryExpr>, add_ptr_typedef<BinaryExpr> {
public:

    AbsExpr::ptr lOperand;
    Token op;
    AbsExpr::ptr rOperand;
}; 

class UnaryExpr : public Visitable<UnaryExpr> {
public:

    Token op;
    AbsExpr::ptr rOperand;

}; 

class GroupExpr : public Visitable<GroupExpr> {
public:

    AbsExpr::ptr subExpr;
}; 


class LiteralExpr : public Visitable<LiteralExpr>, add_ptr_typedef<LiteralExpr> {
public:
    Token literal;
}; 






#endif // EXPRESSION_H