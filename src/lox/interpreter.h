#ifndef EVALUATOR_H
#define EVALUATOR_H
#include <map>
#include <vector>
#include <exception>
#include "visitor_instance.h"
#include "expression.h"
#include "stmt.h"


class RetPortGun: public std::exception {
public:
    // 构造函数，接收错误消息
    // explicit bad_operator(const std::string& message) : message_(message) {}
    explicit RetPortGun(AnyResult::ptr value) : returnValue(std::move(value)) {}

    // 重写 what() 函数，返回错误消息
    const char* what() const noexcept override {
        return "Return statements";
    }

public:
    AnyResult::ptr returnValue;
};

class Environment {
public:
    Environment() = default;
    Environment(std::shared_ptr<Environment> parent): parentEnv(parent) {}
    AnyResult::ptr get(const std::string& key)
    {
        if (symbols.find(key) != symbols.end()) {
            return symbols[key];
        }
        return nullptr;
    }

    void define(const std::string& key, AnyResult::ptr value)
    {
        symbols[key] = value;
    }

    bool haveSymbol(const std::string& key) const
    {
        return symbols.find(key) != symbols.end();
    }
public:
    std::shared_ptr<Environment> parentEnv;
private:
    std::map<std::string, AnyResult::ptr> symbols;
};


class Interpreter: public InterpreteVisitor {
private:
    std::shared_ptr<Environment> scopedEnvChain;
    std::shared_ptr<Environment> globalEnv;
    std::reference_wrapper<std::ostream> output;
public:
    std::shared_ptr<Environment> globalEnvironment() const { return globalEnv; }
public:
    Interpreter(): scopedEnvChain(std::make_shared<Environment>()), 
                    globalEnv(scopedEnvChain), output(std::cout) {}
    void setOutput(std::ostream& out);
public:
    void interprete(const std::vector<AbsStmt::ptr>& stmts);
    void execute(AbsStmt::ptr stmt);
    AnyResult::ptr execute(std::vector<AbsStmt::ptr>& stmts, std::shared_ptr<Environment> environment);
    AnyResult::ptr findSymbol(const std::string& symbol);
    AnyResult::ptr evaluate(AbsExpr::ptr expr);
    AnyResult::ptr visit(BinaryExpr* expr) override;
    AnyResult::ptr visit(UnaryExpr* expr) override;
    AnyResult::ptr visit(GroupExpr* expr) override;
    AnyResult::ptr visit(LiteralExpr* expr) override;
    AnyResult::ptr visit(Variable* expr) override;
    AnyResult::ptr visit(AssignExpr* expr) override;
    AnyResult::ptr visit(CallExpr* expr) override;
    AnyResult::ptr visit(PrintStmt* expr) override;
    AnyResult::ptr visit(ExprStmt* expr) override;
    AnyResult::ptr visit(BlockStmt* expr) override;
    AnyResult::ptr visit(VarDecl* expr) override;
    AnyResult::ptr visit(StmtDecl* expr) override;
    AnyResult::ptr visit(ClassDecl* decl) override;
    AnyResult::ptr visit(FuncDecl* decl) override;
    AnyResult::ptr visit(IfStmt* stmt) override;
    AnyResult::ptr visit(ForStmt* stmt) override;
    AnyResult::ptr visit(WhileStmt* stmt) override;
    AnyResult::ptr visit(ReturnStmt* stmt) override;
};


#endif // EVALUATOR_H