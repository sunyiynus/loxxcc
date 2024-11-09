#ifndef DECL_H
#define DECL_H
#include "common.h"
#include "visitor.h"
#include "visitor_instance.h"
#include "expression.h"

class AbsDecl {
public:
    using ptr = std::shared_ptr<AbsDecl>;
    virtual AnyResult::ptr accept(InterpreteVisitor* visitor) = 0;
};


template<typename DerivedT, typename PT = AbsDecl, typename VT = InterpreteVisitor>
using VisitableDecl = Visitable<DerivedT, PT, VT>;

class VarDecl : public VisitableDecl<VarDecl> {
public:
    static ptr create(const Token& tk, AbsExpr::ptr expr) {
        auto res = std::make_shared<VarDecl>();
        res->identifier = tk;
        res->expression = expr;
        return std::static_pointer_cast<AbsDecl::ptr::element_type>(res);
    }
public:
    Token identifier;
    AbsExpr::ptr expression;
public: 
    using VisitableDecl<VarDecl>::accept;
};


#endif // DECL_H