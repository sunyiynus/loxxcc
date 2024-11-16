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
    std::string generateDot(const std::string file = "") {
        std::ostringstream tmposs;
        tmposs << "digraph AST {\n";
        tmposs << "subgraph cluster_A {\n";
        tmposs << "  label=\"" << file <<"\";\n";
        tmposs << "  node [shape=records];\n";
        tmposs << oss.str();
        tmposs << "}\n}\n";
        return tmposs.str();
    }

    // 获取节点的唯一 ID，如果尚未分配，则分配一个新 ID
    int getId(AbsStmt* node) {
        if (stmtIds.find(node) == stmtIds.end()) {
            stmtIds[node] = ++idCounter;
        }
        return stmtIds[node];
    }

    // 获取节点的唯一 ID，如果尚未分配，则分配一个新 ID
    int getId(AbsExpr* node) {
        if (exprIds.find(node) == exprIds.end()) {
            exprIds[node] = ++idCounter;
        }
        return exprIds[node];
    }

    template <typename T, typename T1>
    void pointTo(T* ptr, T1* ptr1) {
        if (ptr && ptr1) {
            oss << "  " << getId(ptr) << " -> " << getId(ptr1) << ";\n";
        }
    }

    void pointTo(const int p, const int t) {
        oss << "  " << p << " -> " << t << ";\n";
    }

    void defineNode(const int nodeId, const std::string nodeName, const std::string attr) {
        oss << "  " << nodeId << " [label=\"" << nodeName <<" " << attr << "\"];\n";
    }
    template<typename T>
    int defineNode(T* ptr, const std::string nodeName, const std::string attr = "") {
        oss << "  " << getId(ptr) << " [label=\"" << nodeName <<" " << attr << "\"];\n";
        return getId(ptr);
    }

    int appendNode(int parentId, const std::string nodeName, const std::string attr = "") {
        auto id = ++idCounter;
        defineNode(id, nodeName, "");
        pointTo(parentId, id);
        return id;
    }

    template<typename T>
    int appendNode(T* n, const std::string nodeName, const std::string attr = "") {
        auto id = getId(n);
        return appendNode(id, nodeName, attr);
    }

    void iteralStmts(int rootId, const std::vector<AbsStmt::ptr>& stmts) {
        for (const auto& stmt : stmts) {
            if (stmt) {
                stmt->accept(this);
                pointTo(rootId, getId(stmt.get()));
            }
        }
    }

    template<typename T>
    AnyResult::ptr callAccept(std::shared_ptr<T> ptr) {
        if (ptr) {
            return ptr->accept(this);
        }
        return nullptr;
    }

private:
    int idCounter = 0; // 节点计数器，用于生成唯一 ID
    std::ostringstream oss;
    std::unordered_map<AbsStmt*, int> stmtIds; // 节点到 ID 的映射
    std::unordered_map<AbsExpr*, int> exprIds; // 节点到 ID 的映射

};




#endif // PRINTER_H