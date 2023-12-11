#ifndef STMT_H
#define STMT_H

#include "visitor.h"
#include "visitor_instance.h"

class AbsStmt {
public:
    using ptr = std::shared_ptr<AbsStmt>;
    virtual VisitorAbsResult::ptr accept(AstPrinter* visitor) = 0;
};


template<typename DerivedT, typename PT = AbsStmt, typename VT = AstPrinter>
using VisitableStmt = Visitable<DerivedT, PT, VT>;


class PrintStmt : VisitableStmt<PrintStmt> {
public: 
    static ptr create() {

    }
public: 


};

class ExprStmt : VisitableStmt<ExprStmt> {
public: 
    static ptr create() {

    }
};

#endif