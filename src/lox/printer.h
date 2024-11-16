#ifndef PRINTER_H
#define PRINTER_H
#include <sstream>
#include <unordered_map>
#include "expression.h"
#include "stmt.h"


class Printer : public InterpreteVisitor {
public:
    Printer(): output(std::cout) {}
    void setOutput(std::ostream& out);
    std::reference_wrapper<std::ostream> output;
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

    // 递归遍历节点并生成 DOT 代码
    void execute(std::vector<AbsStmt::ptr> stmts) {
        if (stmts.empty()) return;
        for (const auto& stmt : stmts) {
            if (stmt) {
                stmt->accept(this);
            }
        }
    }

    // 生成 DOT 表示的入口函数
    std::string generateDot() {
        std::ostringstream tmposs;
        tmposs << "digraph AST {\n";
        tmposs << "  node [shape=records];\n";
        tmposs << oss.str();
        tmposs << "}\n";
        return tmposs.str();
    }

    // 获取节点的唯一 ID，如果尚未分配，则分配一个新 ID
    int getStmtId(AbsStmt* node) {
        if (stmtIds.find(node) == stmtIds.end()) {
            stmtIds[node] = idCounter++;
        }
        return stmtIds[node];
    }

    // 获取节点的唯一 ID，如果尚未分配，则分配一个新 ID
    int getExprId(AbsExpr* node) {
        if (exprIds.find(node) == exprIds.end()) {
            exprIds[node] = idCounter++;
        }
        return exprIds[node];
    }

    void pointTo(const int nodeId, const int p2id) {
        oss << "  " << nodeId << " -> " << p2id << ";\n";
    }

    void defineNode(const int nodeId, const std::string nodeName, const std::string attr)
    {
        oss << "  " << nodeId << " [label=\"" << nodeName <<" " << attr << "\"];\n";
    }

private:
    int idCounter = 0; // 节点计数器，用于生成唯一 ID
    std::ostringstream oss;
    std::unordered_map<AbsStmt*, int> stmtIds; // 节点到 ID 的映射
    std::unordered_map<AbsExpr*, int> exprIds; // 节点到 ID 的映射

};




#endif // PRINTER_H