#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <memory>
#include <string>
#include "common.h"
#include "visitor.h"
#include "visitor_instance.h"



class AbsExpr {
public:
    using ptr = std::shared_ptr<AbsExpr>;
    virtual AnyResult::ptr accept(InterpreteVisitor* visitor) = 0;
private:
};

template<typename DeriveT, typename PT = AbsExpr, typename VT = InterpreteVisitor>
using VisitableExpr = Visitable<DeriveT, PT, VT>;



class BinaryExpr : public VisitableExpr<BinaryExpr> {
public: 
    static ptr create(const AbsExpr::ptr& lp, const Token& opp, const AbsExpr::ptr& rp) {
        auto res     = std::make_shared<BinaryExpr>();
             res->op = opp;
             res->lOperand = lp;
             res->rOperand = rp;
        return std::static_pointer_cast<AbsExpr::ptr::element_type>(res);
    }
public:
    BinaryExpr() = default;
    AbsExpr::ptr lOperand;
    Token op;
    AbsExpr::ptr rOperand;
};


class UnaryExpr : public VisitableExpr<UnaryExpr> {
public:
    static ptr create(const Token& opp, AbsExpr::ptr rp) {
        auto res           = std::make_shared<UnaryExpr>();
             res->op       = opp;
             res->rOperand = rp;
        return res;
    }
public:
    UnaryExpr() = default;
    Token op;
    AbsExpr::ptr rOperand;

};


class GroupExpr : public VisitableExpr<GroupExpr> {
public:
    static ptr create(AbsExpr::ptr rp) {
        auto res           = std::make_shared<GroupExpr>();
             res->subExpr = rp;
        return res;
    }

public:
    GroupExpr() = default;
    AbsExpr::ptr subExpr;
}; 


class LiteralExpr : public VisitableExpr<LiteralExpr> {
public:
    static ptr create(const Token& rp) {
        auto res     = std::make_shared<LiteralExpr>();
        res->literal = rp;
        return res;
    }
public:
    LiteralExpr() = default;
    Token literal;
};


class Variable : public VisitableExpr<Variable> {
public:
    static ptr create(const Token& rp) {
        auto res     = std::make_shared<Variable>();
        res->literal = rp;
        return res;
    }
public:
    Variable() = default;
    Token literal;
}; 


class AssignExpr : public VisitableExpr<AssignExpr> {
public:
    static ptr create(const Token& rp, AbsExpr::ptr expr) {
        auto res     = std::make_shared<AssignExpr>();
        res->literal = rp;
        res->expression = expr;
        return res;
    }
public:
    AssignExpr() = default;
    Token literal;
    AbsExpr::ptr expression;
}; 


class CallExpr : public VisitableExpr<CallExpr> {
public:
    static ptr create(AbsExpr::ptr clee, const Token& rp, std::vector<AbsExpr::ptr> exprs) {
        auto res     = std::make_shared<CallExpr>();
        res->callee = clee;
        res->identifier = rp;
        res->args = exprs;
        return res;
    }
public:
    CallExpr() = default;
    AbsExpr::ptr callee;
    Token identifier;
    std::vector<AbsExpr::ptr> args;
}; 


#endif // EXPRESSION_H