%я реализовал сложный вариант, тесты проходят. Можно ли поставить M за задачу?
%тесты проходят только простой вариант
init(MAX_N) :-
    initToN(2, MAX_N).

initToN(1, MAX_N) :-
    false.
initToN(X, MAX_N) :-
	Xpow2 is X * X,
	saveCash(Xpow2, X, MAX_N),!.
initToN(X, MAX_N) :-
    Xnext is X + 1,
    XnextPow2 is Xnext * Xnext,
    XnextPow2 =< MAX_N,
    initToN(Xnext, MAX_N).

saveCash(XpowY, X, MAX_N) :-
    XpowY =< MAX_N,
    assert(composite(XpowY)),
    assert(data_Divisors(XpowY, X)),
    XpowYplus1 is XpowY + X,
    XpowYplus1 =< MAX_N,
    saveCash(XpowYplus1, X, MAX_N).

composite(1) :-
    true.
prime(1) :-
    false.
prime(N) :-
    N > 1,
    \+ composite(N).

data_Divisors(X, Y) :-
    X = Y,
    prime(X).

prime_divisors(1, []) :- !.
prime(1, D, []) :- !.

prime_divisors(N, [D | Divisors]) :-
	number(D),
	ND is N * D,
	prime(N, D, [D | Divisors], ND),
	 !.

prime_divisors(N, [D | Divisors]) :-
	data_Divisors(N, D),
	prime(D),
	0 is mod (N, D),
	NdivD is div (N, D),
	prime_divisors(NdivD, Divisors),
	!.

prime_divisors_delete(N, D1, [D2 | Divisors], LastN) :-
    LastN is N * D1,
	D1 =< D2,
	prime_divisors_delete(NdivD, D2, Divisors, N).

unique_prime_divisors(N, Unique) :-
    prime_divisors(N, Divisors),
    delete([], Unique, Divisors, 1).

delete(Unique, Unique, [], DeleteD) :-!.

delete( DivisorsNew, Unique, [D | Divisors], DeleteD) :-
    D > DeleteD,
    append(DivisorsNew, [D], DivisorsNewGet),
    delete(DivisorsNewGet, Unique, Divisors, D).

delete(DivisorsNew, Unique, [D | Divisors], D) :-
    delete(DivisorsNew, Unique, Divisors, D).