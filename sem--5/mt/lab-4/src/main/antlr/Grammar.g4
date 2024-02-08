grammar Grammar;

file
    : (start rule+)? EOF
    ;

start
    : '<start>' NONTERM
    ;

rule
	: rParse ';'
	| rLex ';'
	;

rParse
    : NONTERM inherited? ('->' synthesized)? ':=' production* ('|' production*)*
    ;

inherited
    : '<' param (',' param)* '>'
    ;

param
    : NONTERM '->' TERM
    ;

synthesized
    : TERM
    ;

production
    : NONTERM ('(' argument (',' argument)* ')')?
    | TERM
    | CODE
    ;

argument
    : NONTERM
    | TERM
    | CODE
    ;

rLex
	: TERM ':' term_value # tokenLex
	| TERM ':>' term_value # skipLex
	;

term_value
	: REG
	| STRING
	;

NONTERM
    : [a-z][a-zA-Z0-9]*
    ;

TERM
    : [A-Z][a-zA-Z0-9]*
    ;

REG
    : '\'' (~('\''|'\r' | '\n') | '\\\'')* '\''
       ;

STRING
    : '"' (~('"') | '\\"')* '"'
    ;

CODE
    : '#<' (~[#<>}]+ CODE?)* '>'
    ;

WS
    : [ \t\r\n]+ -> skip
    ;
