nonvar(V, _) :- var(V).
nonvar(V, T) :- nonvar(V), call(T).

skipWS --> [].
skipWS --> [' '], skipWS.

:- load_library('alice.tuprolog.lib.DCGLibrary').

expr_p(variable(Name)) --> 
	skipWS,
	[Name],
	skipWS,
	{ member(Name, [x, y, z]) }.

expr_p(const(Value)) -->
  { nonvar(Value, number_chars(Value, Chars)) },
	skipWS,
  digits_p(Chars),
  skipWS,
  {\+ (Chars = ['-']), Chars = [_ | _], number_chars(Value, Chars) }.
  
digits_p([]) --> [].
digits_p([H | T]) -->
  { member(H, ['.', '-', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'])},
  [H],
  digits_p(T).

op_p(op_add) --> ['+'].
op_p(op_subtract) --> ['-'].
op_p(op_multiply) --> ['*'].
op_p(op_divide) --> ['/'].
op_p(op_negate) --> [n,e,g,a,t,e].

expr_p(operation(Operation, First, Second)) -->  
	skipWS,
	['('], skipWS,
	expr_p(First),
	[' '], skipWS,
	expr_p(Second),
	[' '], skipWS, 
	op_p(Operation), skipWS,
	[')'], skipWS.

expr_p(operation(Operation, First)) -->  
	skipWS,
	['('], skipWS,
	expr_p(First),
	[' '], skipWS,
	op_p(Operation), skipWS,
	[')'], skipWS.

suffix_str(E, A) :- ground(E), phrase(expr_p(E), C), atom_chars(A, C),!.
suffix_str(E, A) :-   atom(A), atom_chars(A, C), phrase(expr_p(E), C), !.

map_get(Var, [(Var, Value) | T], Value) :- !.
map_get(Var, [H | T], Result) :- map_get(Var, T, Result).

operation(op_add, First, Second, Result) :-
	Result is First + Second.
operation(op_subtract, First, Second, Result) :- 
	Result is First - Second.
operation(op_multiply, First, Second, Result) :- 
	Result is First * Second.
operation(op_divide, First, Second, Result) :- 
	Result is First / Second.
operation(op_negate, First, Result) :- 
	Result is -First.

evaluate(const(Const),  _, Const).
evaluate(variable(Var), Variables, Result) :- 
	map_get(Var, Variables, Result).

evaluate(operation(Operation, First), Variables, Result) :-
    evaluate(First, Variables, FirstNew),
    operation(Operation, FirstNew, Result).
    
evaluate(operation(Operation, First, Second), Variables, Result) :- 
    evaluate(First, Variables, FirstNew), 
    evaluate(Second, Variables, SecondNew), 
    operation(Operation, FirstNew, SecondNew, Result).
    