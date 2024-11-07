
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
class DeclStmt;
class BlockStmt;


using AstVisitor = Visitor<BinaryExpr, UnaryExpr, GroupExpr, LiteralExpr, AssignExpr, \
                            PrintStmt, ExprStmt, DeclStmt, BlockStmt>;

using ExprVisitor = AstVisitor;

using InterpreteVisitor = Visitor<BinaryExpr, UnaryExpr, GroupExpr, LiteralExpr, AssignExpr, \
                            PrintStmt, ExprStmt, DeclStmt, BlockStmt>;


#endif // VISITOR_INSTANCE_H