#ifndef EVALUATOR_H
#define EVALUATOR_H
#include "visitor_instance.h"

class Interpreter: public InterpreteVisitor {
public: 
    Interpreter() = default;
    VisitorAbsResult::ptr visit(BinaryExpr* expr) override;
    VisitorAbsResult::ptr visit(UnaryExpr* expr) override;
    VisitorAbsResult::ptr visit(GroupExpr* expr) override;
    VisitorAbsResult::ptr visit(LiteralExpr* expr) override;
    VisitorAbsResult::ptr visit(PrintStmt* expr) override;
    VisitorAbsResult::ptr visit(ExprStmt* expr) override;
};


#endif // EVALUATOR_H