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
    static ptr create(std::vector<AbsStmt::ptr> stms) {
        auto res = std::make_shared<BlockStmt>();
        res->stmts = std::move(stms);
        return std::static_pointer_cast<AbsStmt::ptr::element_type>(res);
    }
public:
    std::vector<AbsStmt::ptr> stmts;

public: 
    using VisitableStmt<BlockStmt>::accept;

};


class IfStmt : public VisitableStmt<IfStmt> {
public: 
    static ptr create(AbsExpr::ptr ce, std::vector<AbsStmt::ptr> trueStmts,  std::vector<AbsStmt::ptr> elseStmts) {
        auto res = std::make_shared<IfStmt>();
        res->checkExpression = ce;
        res->trueStmts = std::move(trueStmts);
        res->elseStmts = std::move(elseStmts);
        return std::static_pointer_cast<AbsStmt::ptr::element_type>(res);
    }
public:
    AbsExpr::ptr checkExpression;
    std::vector<AbsStmt::ptr> trueStmts;
    std::vector<AbsStmt::ptr> elseStmts;

public: 
    using VisitableStmt<IfStmt>::accept;
};


class ForStmt : public VisitableStmt<ForStmt> {
public: 
    static ptr create(AbsStmt::ptr init, AbsExpr::ptr cond, AbsExpr::ptr update, std::vector<AbsStmt::ptr> stmts) {
        auto res = std::make_shared<ForStmt>();
        res->initializationStmt = init;
        res->conditionExpr = cond;
        res->updateStmt = update;
        res->stmts = std::move(stmts);
        return std::static_pointer_cast<AbsStmt::ptr::element_type>(res);
    }
public:
    AbsStmt::ptr initializationStmt;
    AbsExpr::ptr conditionExpr;
    AbsExpr::ptr updateStmt;
    std::vector<AbsStmt::ptr> stmts;
public: 
    using VisitableStmt<ForStmt>::accept;
};


class WhileStmt : public VisitableStmt<WhileStmt> {
public: 
    static ptr create(AbsExpr::ptr cond,std::vector<AbsStmt::ptr> stms) {
        auto res = std::make_shared<WhileStmt>();
        res->condition = cond;
        res->stmts = std::move(stms);
        return std::static_pointer_cast<AbsStmt::ptr::element_type>(res);
    }
public:
    AbsExpr::ptr condition;
    std::vector<AbsStmt::ptr> stmts;

public: 
    using VisitableStmt<WhileStmt>::accept;
};


class ReturnStmt : public VisitableStmt<ReturnStmt> {
public: 
    static ptr create(AbsExpr::ptr expr) {
        auto res = std::make_shared<ReturnStmt>();
        res->expression = expr;
        return std::static_pointer_cast<AbsStmt::ptr::element_type>(res);
    }
public:
    AbsExpr::ptr expression;
public: 
    using VisitableStmt<ReturnStmt>::accept;
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


class FuncDecl : public VisitableDecl<FuncDecl> {
public:
    static ptr create(const Token& fname, Tokens tk, std::vector<AbsStmt::ptr> stmt) {
        auto res = std::make_shared<FuncDecl>();
        res->funcName = fname;
        res->parameter = std::move(tk);
        res->stmts = std::move(stmt);
        return std::static_pointer_cast<AbsStmt::ptr::element_type>(res);
    }
public:
    Token funcName;
    Tokens parameter;
    std::vector<AbsStmt::ptr> stmts;
public: 
    using VisitableDecl<FuncDecl>::accept;
    using ptr = std::shared_ptr<FuncDecl>;
};


class ClassDecl : public VisitableDecl<ClassDecl> {
public:
    static ptr create(AbsStmt::ptr stmt) {
        auto res = std::make_shared<StmtDecl>();
        res->stmt = std::move(stmt);
        return std::static_pointer_cast<AbsStmt::ptr::element_type>(res);
    }
public:
    std::vector<FuncDecl::ptr> functions;
    Token className;
public: 
    using VisitableDecl<ClassDecl>::accept;
};
#endif // STMT_H


