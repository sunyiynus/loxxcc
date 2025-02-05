#include "parser.h"
#include <functional>
#include <list>
#include "errors.h"
#include "format.h"

std::vector<AbsStmt::ptr> Parser::parse() {
    std::vector<AbsStmt::ptr> stmts;

    while (!atEnd()) {
        stmts.push_back(declaration());
    }
    return stmts;
}

const Token& Parser::current()
{
    return *curItr;
}


const Token& Parser::previous()
{
    auto tmpItr = curItr;
    tmpItr--;
    return *tmpItr;
}


bool Parser::atEnd() const {
    return curItr == tokensSeq.end();
}

bool Parser::matchTokens(std::initializer_list<TokenType> tktypes)
{
    auto tmpItr = curItr;
    for (auto tktype:tktypes) {
        if (matchToken(tktype)) {
            return true;
        }
    }
    return false;
}


bool Parser::matchToken(const TokenType tktype)
{
    auto tmpItr = curItr;
    return (!atEnd() && tmpItr->token == tktype) ? true : false;
}


void Parser::advance()
{
    curItr++;
    itrIdx = std::distance(tokensSeq.begin(), curItr);
}


void Parser::synchronize()
{
    std::initializer_list<TokenType> matchTk {TokenType::RIGHT_BRACE, 
                                                TokenType::RIGHT_PAREN,
                                                TokenType::COMMA};
    while (!atEnd()) {
        if (matchTokens(matchTk))
        {
            break;
        }
        advance();
    }
}


void Parser::consume(std::initializer_list<TokenType> tktypes)
{
    if (matchTokens(tktypes)) {
        advance();
        return;
    }

    std::string error = "Have meet unexpect token: " + static_cast<std::string>(current());
    throw bad_grammar(error);
}

AbsExpr::ptr Parser::expression()
{
    return assignExpr();
}

AbsExpr::ptr Parser::equatity()
{
    std::initializer_list<TokenType> matchTk {TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL};
    return this->template binary_expression_reimpl<&Parser::comparsion>(matchTk);
}

AbsExpr::ptr Parser::comparsion()
{
    std::initializer_list<TokenType> matchTk {TokenType::LESS, TokenType::LESS_EQUAL, 
                                                TokenType::GREATER, TokenType::GREATER_EQUAL};
    return this->template binary_expression_reimpl<&Parser::term>(matchTk);
}

AbsExpr::ptr Parser::term()
{
    std::initializer_list<TokenType> matchTk {TokenType::PLUS, TokenType::MINUS}; 
    return this->template binary_expression_reimpl<&Parser::factor>(matchTk);
}

AbsExpr::ptr Parser::factor()
{
    std::initializer_list<TokenType> matchTk {TokenType::SLASH, TokenType::STAR}; 
    return this->template binary_expression_reimpl<&Parser::unary>(matchTk);
}
AbsExpr::ptr Parser::unary()
{
    AbsExpr::ptr subExpr;
    if (matchTokens({TokenType::MINUS, TokenType::BANG})) {
        auto op = current();
        advance();
        subExpr = primary();
        subExpr = UnaryExpr::create(op, subExpr);
    } else {
        subExpr = call();
    }
    return subExpr;
}

AbsExpr::ptr Parser::primary()
{
    if (matchTokens({TokenType::NUMBER, TokenType::STRING})) {
         auto res = LiteralExpr::create(current());
         advance();
         return res;
    }

    if (matchTokens({TokenType::IDENTIFIER})) {
         auto res = Variable::create(current());
         advance();
         return res;
    }

    if (matchTokens({TokenType::TRUE, TokenType::FALSE})) {
        auto res = LiteralExpr::create(current());
        advance();
        return res;
    }

    if (matchTokens({TokenType::LEFT_PAREN})) {
        advance();
        auto expr = expression();
        consume({TokenType::RIGHT_PAREN});
        auto res = GroupExpr::create(expr);
        return res;
    }
    // bad_grammar bg("error at ");
    // throw bg;
    return nullptr;
}

AbsExpr::ptr Parser::assignExpr() 
{   AbsExpr::ptr expr = equatity();
    if (matchTokens({TokenType::EQUAL})) {
        consume({TokenType::EQUAL});
        AbsExpr::ptr value = assignExpr();

        auto tmp = std::dynamic_pointer_cast<Variable>(expr);
        if (tmp) {
            Token tmpTk = tmp->literal;
            return AssignExpr::create(tmpTk, value);
        }
    }
    // consume({TokenType::SEMICOM});
    return expr;
}


AbsExpr::ptr Parser::finishCall(AbsExpr::ptr expr)
{
    consume({TokenType::LEFT_PAREN});
    std::vector<AbsExpr::ptr> args;
    auto identifier = std::dynamic_pointer_cast<Variable>(expr);
    if (!matchToken(TokenType::RIGHT_PAREN)) {
        args = arguments();
    }
    consume({TokenType::RIGHT_PAREN});
    return CallExpr::create(expr, identifier->literal, args);
}


std::vector<AbsExpr::ptr> Parser::arguments()
{
    std::vector<AbsExpr::ptr> args;
    args.push_back(primary());
    while(!atEnd() && !matchTokens({TokenType::RIGHT_PAREN})) {
        consume({TokenType::COMMA});
        args.push_back(primary());
    }
    return args;
}


AbsExpr::ptr Parser::call()
{
    auto expr = primary();
    while (true) {
        if (matchTokens({TokenType::LEFT_PAREN})) {
            expr = finishCall(expr);
        } else {
            break;
        }
    }
    return expr;
}

AbsStmt::ptr Parser::exprStmt()
{
    AbsExpr::ptr expr = expression();
    consume({TokenType::SEMICOM});
    return ExprStmt::create(expr);
}

AbsStmt::ptr Parser::printStmt()
{
    consume({TokenType::PRINT});
    AbsExpr::ptr expr = expression();
    consume({TokenType::SEMICOM});
    return PrintStmt::create(expr);

}

AbsStmt::ptr Parser::blockStmt()
{
    consume({TokenType::LEFT_BRACE});
    std::vector<AbsStmt::ptr> stmts;
    while( !atEnd() && !matchTokens({TokenType::RIGHT_BRACE})) {
        stmts.push_back(declaration());
    }
    consume({TokenType::RIGHT_BRACE});
    return BlockStmt::create(stmts);
}

AbsStmt::ptr Parser::declaration()
{
    try {
        if (matchTokens({TokenType::VAR})) {
            return varDecl();
        }
        if (matchTokens({TokenType::FUNC})) {
            return funcDecl();
        }
        // if (matchTokens({TokenType::CLASS})) {
        //     return classDecl();
        // }
        return statement();
    } catch (const std::exception& e) {
        synchronize();
        return nullptr;
    }
}


AbsStmt::ptr Parser::ifStmt()
{
    consume({TokenType::IF});
    consume({TokenType::LEFT_PAREN});
    auto cond = expression();
    consume({TokenType::RIGHT_PAREN});
    auto ifstmt = std::make_shared<IfStmt>();
    ifstmt->checkExpression = cond;
    if (matchToken(TokenType::LEFT_BRACE)) {
        auto stmts = blockStmt();
        auto tmpStmts = std::dynamic_pointer_cast<BlockStmt>(stmts);
        ifstmt->trueStmts = std::move(tmpStmts->stmts);
    } else {
        ifstmt->trueStmts.push_back(declaration());
    }

    if (matchToken(TokenType::ELSE)) {
        consume({TokenType::ELSE});
        if (matchToken(TokenType::LEFT_BRACE)) {
            auto tmpStmts = std::dynamic_pointer_cast<BlockStmt>(blockStmt());
            ifstmt->elseStmts = std::move(tmpStmts->stmts);
        } else {
            ifstmt->elseStmts.push_back(declaration());
        }

    }
    return ifstmt;
}

AbsStmt::ptr Parser::forStmt()
{
    consume({TokenType::FOR});
    consume({TokenType::LEFT_PAREN});
    auto forstmt = std::make_shared<ForStmt>();
    if (!matchToken(TokenType::SEMICOM)) {
        forstmt->initializationStmt = declaration();
    } else {
        consume({TokenType::SEMICOM});
    }
    if (!matchToken(TokenType::SEMICOM)) {
        forstmt->conditionExpr = expression();
    }
    consume({TokenType::SEMICOM});
    if (!matchToken(TokenType::RIGHT_PAREN)) {
        forstmt->updateStmt = expression();
    }
    consume({TokenType::RIGHT_PAREN});
    if (matchToken(TokenType::LEFT_BRACE)) {
        forstmt->stmts = std::move(std::dynamic_pointer_cast<BlockStmt>(blockStmt())->stmts); 
    } else {
        forstmt->stmts.push_back(statement());
    }
    return forstmt;
}


AbsStmt::ptr Parser::whileStmt()
{
    auto whilestmt = std::make_shared<WhileStmt>();
    consume({TokenType::WHILE});
    consume({TokenType::LEFT_PAREN});
    whilestmt->condition = expression();
    consume({TokenType::RIGHT_PAREN});
    if (matchToken(TokenType::LEFT_BRACE)) {
        whilestmt->stmts = std::move(std::dynamic_pointer_cast<BlockStmt>(blockStmt())->stmts);
    } else {
        whilestmt->stmts.push_back(declaration());
    }
    return whilestmt;
}

AbsStmt::ptr Parser::retStmt()
{
    consume({TokenType::RETURN});
    auto rstmt = std::make_shared<ReturnStmt>();
    rstmt->expression = expression();
    consume({TokenType::SEMICOM});
    return rstmt;
}

AbsStmt::ptr Parser::statement()
{
    AbsStmt::ptr res;
    if (matchTokens({TokenType::PRINT})) {
        res =  printStmt();
        return StmtDecl::create(res);
    }
    if (matchTokens({TokenType::LEFT_BRACE})) {
        res = blockStmt();
        return StmtDecl::create(res);
    }
    if (matchTokens({TokenType::IF})) {
        return ifStmt();
    }
    if (matchTokens({TokenType::FOR})) {
        return forStmt();
    }
    if (matchTokens({TokenType::WHILE})) {
        return whileStmt();
    }
    if (matchToken(TokenType::RETURN)) {
        return retStmt();
    }
    res = exprStmt();
    return StmtDecl::create(res);
}

AbsStmt::ptr Parser::classDecl()
{
    consume({TokenType::CLASS});
    Token className = current();
    advance();
    auto classStmt = std::make_shared<ClassDecl>();
    while (!atEnd() && matchToken(TokenType::LESS)) {
        consume({TokenType::LESS});
        
    }
}

AbsStmt::ptr Parser::varDecl()
{
    consume({TokenType::VAR});
    Token tk = current();
    AbsExpr::ptr expr;
    advance();
    if (matchTokens({TokenType::EQUAL})) {
        advance();
        expr = expression();
    }
    
    consume({TokenType::SEMICOM});
    return VarDecl::create(tk, expr);
}

AbsStmt::ptr Parser::funcDecl()
{
    auto funcPtr = std::make_shared<FuncDecl>();
    consume({TokenType::FUNC});
    funcPtr->funcName = current();
    advance();
    consume({TokenType::LEFT_PAREN});
    if (!matchToken(TokenType::RIGHT_PAREN)) {
        funcPtr->parameter = parameter();
    }
    consume({TokenType::RIGHT_PAREN});
    auto stmts = blockStmt();
    auto tmpStmts = std::dynamic_pointer_cast<BlockStmt>(stmts);
    if (tmpStmts) {
        funcPtr->stmts = std::move(tmpStmts->stmts);
    }
    
    return funcPtr;
}

Tokens Parser::parameter()
{
    Tokens tks;
    tks.emplace_back(current());
    while (!atEnd() && !matchTokens({TokenType::RIGHT_PAREN})) {
        consume({TokenType::COMMA});
        tks.emplace_back(current());
        advance();
    }
    return tks;
}
