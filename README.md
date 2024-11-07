Second trying for writing a interpreter.

------
#### Progress
1. Lexer DONE
   - Not finish error handle
2. Parser
    - Expresion
    - Statement
    - PrinterVisitor
    - EvaluateVisitor
    - decent parser
      - expresion parser
      - statement parser
3. Vm



4 [Syntax Grammar](https://craftinginterpreters.com/appendix-i.html)

```
program -> declare * EOF ;

declare -> vardecl | statement ;

statement -> block_stmt | print_stmt | expr_stmt ;

block_stmt -> "{" declare * "}" ;

print_stmt -> "print" expr_stmt ";" ;

vardecl -> "var" primary ("=" expr_stmt) ? ";" ;

expr_stmt -> expression

expression -> unary | binary | group | literal

literal -> primary

primary -> "true" | "false" | "nill"
            | NUMBER | STRING
            | "(" expression ")"
            | IDENTIFIER ;

```