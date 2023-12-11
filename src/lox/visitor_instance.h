
#ifndef VISITOR_INSTANCE_H
#define VISITOR_INSTANCE_H

#include "visitor.h"

class BinaryExpr;
class UnaryExpr;
class GroupExpr;
class LiteralExpr;
class PrintStmt;
class ExprStmt;
using AstVisitor = Visitor<BinaryExpr, UnaryExpr, GroupExpr, LiteralExpr, \
                            PrintStmt, ExprStmt>;

using ExprVisitor = AstVisitor;

using InterpreteVisitor = Visitor<BinaryExpr, UnaryExpr, GroupExpr, LiteralExpr, \
                            PrintStmt, ExprStmt>;


#endif // VISITOR_INSTANCE_H