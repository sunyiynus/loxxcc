#ifndef STMT_H
#define STMT_H
#include <memory>
#include "visitor.h"
#include "visitor_instance.h"

class AbsStmt {
public:
    using ptr = std::shared_ptr<AbsStmt>;
    virtual AnyResult::ptr accept(AstVisitor* visitor) = 0;
};


template<typename DerivedT, typename PT = AbsStmt, typename VT = AstVisitor>
using VisitableStmt = Visitable<DerivedT, PT, VT>;


class PrintStmt : VisitableStmt<PrintStmt> {
public:
    static ptr create(AbsExpr::ptr expr) {
        auto res = std::make_shared<PrintStmt>();
        res->expression = expr;
        return std::static_pointer_cast<AbsExpr::ptr::element_type>(res);
    }
public:
    AbsExpr::ptr expression;
public: 
    using VisitableStmt<PrintStmt>::accept;
};

class ExprStmt : VisitableStmt<ExprStmt> {
public: 
    static ptr create(AbsExpr::ptr expr) {
        auto res = std::make_shared<ExprStmt>();
        res->expression = expr;
        return std::static_pointer_cast<AbsExpr::ptr::element_type>(res);
    }
public:
    AbsExpr::ptr expression;
public: 
    using VisitableStmt<ExprStmt>::accept;

};


class DeclStmt : VisitableStmt<DeclStmt> {
public: 
    static ptr create(const Token& tk, AbsExpr::ptr expr) {
        auto res = std::make_shared<DeclStmt>();
        res->expression = expr;
        res->tk = tk;
        return std::static_pointer_cast<AbsExpr::ptr::element_type>(res);
    }
public:
    Token tk;
    AbsExpr::ptr expression;

public: 
    using VisitableStmt<DeclStmt>::accept;

};

class BlockStmt : VisitableStmt<BlockStmt> {
public: 
    static ptr create(std::list<AbsStmt::ptr> stmts) {
        auto res = std::make_shared<BlockStmt>();
        res->stmts = stmts;
        return std::static_pointer_cast<AbsStmt::ptr::element_type>(res);
    }
public:
    std::list<AbsStmt::ptr> stmts;

public: 
    using VisitableStmt<BlockStmt>::accept;

};




#endif // STMT_H


