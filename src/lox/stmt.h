#ifndef STMT_H
#define STMT_H

#include "visitor.h"
#include "visitor_instance.h"

class AbsStmt {
public:
    using ptr = std::shared_ptr<AbsStmt>;
    virtual VisitorAbsResult::ptr accept(AstVisitor* visitor) = 0;
};


template<typename DerivedT, typename PT = AbsStmt, typename VT = AstVisitor>
using VisitableStmt = Visitable<DerivedT, PT, VT>;


class PrintStmt : VisitableStmt<PrintStmt> {
public:
    template <typename ...Args>
    static ptr create(Args...) {

    }
public: 
    using VisitableStmt<PrintStmt>::accept;
};

class ExprStmt : VisitableStmt<ExprStmt> {
public: 
    static ptr create() {

    }
public: 
    using VisitableStmt<ExprStmt>::accept;

};

#endif


