#ifndef DECL_H
#define DECL_H
#include "common.h"
#include "visitor.h"
#include "visitor_instance.h"
#include "expression.h"
#include "stmt.h"

class AbsDecl {
public:
    using ptr = std::shared_ptr<AbsDecl>;
    virtual AnyResult::ptr accept(InterpreteVisitor* visitor) = 0;
};


template<typename DerivedT, typename PT = AbsDecl, typename VT = InterpreteVisitor>
using VisitableDecl = Visitable<DerivedT, PT, VT>;

class VarDecl : public VisitableDecl<VarDecl> {
public:
    static ptr create(const Token& tk, AbsExpr::ptr expr) {
        auto res = std::make_shared<VarDecl>();
        res->identifier = tk;
        res->expression = expr;
        return std::static_pointer_cast<AbsDecl::ptr::element_type>(res);
    }
public:
    Token identifier;
    AbsExpr::ptr expression;
public: 
    using VisitableDecl<VarDecl>::accept;
};


class StmtDecl : public VisitableDecl<StmtDecl> {
public:
    static ptr create(AbsStmt::ptr stmt) {
        auto res = std::make_shared<StmtDecl>();
        res->stmt = stmt;
        return std::static_pointer_cast<AbsDecl::ptr::element_type>(res);
    }
public:
    AbsStmt::ptr stmt;
public: 
    using VisitableDecl<StmtDecl>::accept;
};


#endif // DECL_H