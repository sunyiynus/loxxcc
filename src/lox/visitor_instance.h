
#ifndef VISITOR_INSTANCE_H
#define VISITOR_INSTANCE_H

#include "visitor.h"

class BinaryExpr;
class UnaryExpr;
class GroupExpr;
class LiteralExpr;
class AssignExpr;
class CallExpr;
class PrintStmt;
class ExprStmt;
class BlockStmt;
class VarDecl;
class StmtDecl;
class Variable;
class ClassDecl;
class FuncDecl;
class ForStmt;
class IfStmt;
class ReturnStmt;
class WhileStmt;

using InterpreteVisitor = Visitor<BinaryExpr, UnaryExpr, GroupExpr, LiteralExpr, Variable, AssignExpr, \
                            PrintStmt, ExprStmt, BlockStmt, VarDecl, StmtDecl, ClassDecl, FuncDecl,
                            ForStmt, IfStmt, ReturnStmt, WhileStmt, CallExpr>;


#endif // VISITOR_INSTANCE_H