#ifndef EVALUATOR_H
#define EVALUATOR_H
#include "visitor_instance.h"



class Environment {
public:
    Environment(std::shared_ptr<Environment> parent): parentEnv(parent) {}
    AnyResult::ptr get(const std::string& key);
    void set(const std::string& key, AnyResult::ptr value);
private:
    std::map<std::string, Any> symbols;
    std::shared_ptr<Environment> parentEnv;
};

class Interpreter: public InterpreteVisitor {
private:

public: 
    Interpreter() = default;
    AnyResult::ptr visit(BinaryExpr* expr) override;
    AnyResult::ptr visit(UnaryExpr* expr) override;
    AnyResult::ptr visit(GroupExpr* expr) override;
    AnyResult::ptr visit(LiteralExpr* expr) override;
    AnyResult::ptr visit(AssignExpr* expr) override;
    AnyResult::ptr visit(PrintStmt* expr) override;
    AnyResult::ptr visit(ExprStmt* expr) override;
    AnyResult::ptr visit(DeclStmt* expr) override;
};


#endif // EVALUATOR_H