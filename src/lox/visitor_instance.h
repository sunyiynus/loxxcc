
#ifndef VISITOR_INSTANCE_H
#define VISITOR_INSTANCE_H

#include "visitor.h"

class BinaryExpr;
class UnaryExpr;
class GroupExpr;
class LiteralExpr;
using AstPrinter  = Visitor<BinaryExpr, UnaryExpr, GroupExpr, LiteralExpr>;
using ExprVisitor = AstPrinter;

#endif // VISITOR_INSTANCE_H