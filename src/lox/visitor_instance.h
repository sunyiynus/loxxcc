
#ifndef VISITOR_INSTANCE_H
#define VISITOR_INSTANCE_H

#include "visitor.h"

class BinaryExpr;
class UnaryExpr;
class GroupExpr;
class LiteralExpr;
class AssignExpr;
class PrintStmt;
class ExprStmt;
class BlockStmt;
class VarDecl;
class StmtDecl;
class Variable;

using InterpreteVisitor = Visitor<BinaryExpr, UnaryExpr, GroupExpr, LiteralExpr, Variable, AssignExpr, \
                            PrintStmt, ExprStmt, BlockStmt, VarDecl, StmtDecl>;


#endif // VISITOR_INSTANCE_H