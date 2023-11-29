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


class BinaryExpr : public Visitable<BinaryExpr> {
public:

private:
    Token leftOpand;
}; 

class UnaryExpr : public Visitable<UnaryExpr> {
public:

}; 

class GroupExpr : public Visitable<GroupExpr> {
public:

}; 

class LiteralExpr : public Visitable<LiteralExpr> {
public:

}; 






#endif // EXPRESSION_H