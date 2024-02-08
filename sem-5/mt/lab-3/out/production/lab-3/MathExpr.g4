grammar MathExpr;

let
    : state+
    ;

state
    : VAR '=' expr LS           # newState
    ;


expr
    : 'C' '(' expr ',' expr ')' # exprCnk
    | expr op=('*'|'/') expr    # exprMulDiv
    | expr op=('+'|'-') expr    # exprAddSub
    | '(' expr ')'              # exprParens
    | INT                       # exprInt
    | VAR                       # exprVar
    ;

ADD
    : '+'
    ;

SUB
    : '-'
    ;

MUL
    : '*'
    ;

DIV
    : '/'
    ;

INT
    : '0'
    | '-'?[1-9][0-9]*
    ;

VAR
    : [a-zA-Z]+
    ;

LS
    : ';'
    ;
WS
    : [ \t\n\r]+ -> skip
    ;

