#ifndef STMT_H
#define STMT_H
#include <memory>
#include <list>
#include "visitor.h"
#include "visitor_instance.h"

class AbsStmt {
public:
    using ptr = std::shared_ptr<AbsStmt>;
    virtual AnyResult::ptr accept(InterpreteVisitor* visitor) = 0;
};


template<typename DerivedT, typename PT = AbsStmt, typename VT = InterpreteVisitor>
using VisitableStmt = Visitable<DerivedT, PT, VT>;


class PrintStmt : public VisitableStmt<PrintStmt> {
public:
    static ptr create(AbsExpr::ptr expr) {
        auto res = std::make_shared<PrintStmt>();
        res->expression = expr;
        return std::static_pointer_cast<AbsStmt::ptr::element_type>(res);
    }
public:
    AbsExpr::ptr expression;
public: 
    using VisitableStmt<PrintStmt>::accept;
};

class ExprStmt : public VisitableStmt<ExprStmt> {
public: 
    static ptr create(AbsExpr::ptr expr) {
        auto res = std::make_shared<ExprStmt>();
        res->expression = expr;
        return std::static_pointer_cast<AbsStmt::ptr::element_type>(res);
    }
public:
    AbsExpr::ptr expression;
public: 
    using VisitableStmt<ExprStmt>::accept;
};


class BlockStmt : public VisitableStmt<BlockStmt> {
public: 
    static ptr create(std::list<AbsStmt::ptr> stms) {
        auto res = std::make_shared<BlockStmt>();
        res->stmts = std::move(stms);
        return std::static_pointer_cast<AbsStmt::ptr::element_type>(res);
    }
public:
    std::list<AbsStmt::ptr> stmts;

public: 
    using VisitableStmt<BlockStmt>::accept;

};


template<typename DerivedT, typename PT = AbsStmt, typename VT = InterpreteVisitor>
using VisitableDecl = Visitable<DerivedT, PT, VT>;

class VarDecl : public VisitableDecl<VarDecl> {
public:
    static ptr create(const Token& tk, AbsExpr::ptr expr) {
        auto res = std::make_shared<VarDecl>();
        res->identifier = tk;
        res->expression = expr;
        return std::static_pointer_cast<AbsStmt::ptr::element_type>(res);
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
        res->stmt = std::move(stmt);
        return std::static_pointer_cast<AbsStmt::ptr::element_type>(res);
    }
public:
    AbsStmt::ptr stmt;
public: 
    using VisitableDecl<StmtDecl>::accept;
};



#endif // STMT_H


