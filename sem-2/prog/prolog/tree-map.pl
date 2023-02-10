
log2(1, 0) :- !.
log2(N, H):-
	N1 is div(N, 2),
	log2(N1, H1),
	H is H1 + 1.

init(ListMap, N, NeedHight):-
	length(ListMap, N), 
	log2(N, NeedHight).
	
build([], [], TreeMap, IsHight, NeedHight, TreeMap) :-!.
build(ListMap, ListMap, TreeMap, NeedHight, NeedHight, TreeMap) :-!.

build([Pair | Tail], TailFromLeft, Left, IsHight, NeedHight, TreeMap) :-
	IsHight1 is IsHight + 1,
	build(Tail, TailFromRight, null, 0, IsHight, Right),
	NewNode = node(Left, Right, Pair),
	build(TailFromRight, TailFromLeft, NewNode, IsHight1, NeedHight, TreeMap).
	
map_build([], []) :-!.	
map_build(ListMap, TreeMap) :-
	init(ListMap, N, NeedHight),
	build(ListMap, [], null, 0, NeedHight,TreeMap),
	!.
	
map_get(node(_, _,(Key, Value)), Key, Value) :- !.
map_get(node(Left, Right,(KeyThis, ValueThis)), Key, Value) :-
	KeyThis < Key,
	map_get(Right, Key, Value).

map_get(node(Left, Right,(KeyThis, ValueThis)), Key, Value) :-
	Key < KeyThis,
	map_get(Left, Key, Value).

map_minKey(node(null, E,(K, V)), K):- !.
map_minKey(node(L, R,(K, V)), Key):-
	map_minKey(L, Key).

map_maxKey(node(E, null, (K, V)), K):- !.
map_maxKey(node(L, R, (K, V)), Key):-
	map_maxKey(R, Key).
				