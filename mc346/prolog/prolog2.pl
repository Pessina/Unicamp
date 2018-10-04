% Encontra elemento tree
findElement(X, tree(X, _, _)).
findElement(Elem, tree(X, AL, AR)) :- Elem < X, findElement(Elem, AL).
findElement(Elem, tree(X, AL, AR)) :- findElement(Elem, AR).

% Check if is ABB
getMinTree(tree(Min, nil, nil), Min).
getMinTree(tree(X, AL, AR), Min) :- getMinTree(AL, Min1), getMinTree(AR, Min2), Min1 < Min2, Min1 < X, Min is Min1.
getMinTree(tree(X, AL, AR), Min) :- getMinTree(AL, Min1), getMinTree(AR, Min2), Min2 < X, Min is Min2.
getMinTree(tree(X, AL, AR), Min) :- getMinTree(AL, Min1), getMinTree(AR, Min2), Min is X .

getMaxTree(tree(Max, nil, nil), Max).
getMaxTree(tree(X, AL, AR), Max) :- getMaxTree(AL, Max1), getMaxTree(AR, Max2), Max1 > Max2, Max1 > X, Max is Max1.
getMaxTree(tree(X, AL, AR), Max) :- getMaxTree(AL, Max1), getMaxTree(AR, Max2), Max2 > X, Max is Max2.
getMaxTree(tree(X, AL, AR), Max) :- getMaxTree(AL, Max1), getMaxTree(AR, Max2), Max is X .

checkABB(tree(X, nil, nil)).
checkABB(tree(X, AL, AR)) :- getMaxTree(AL, Max), getMinTree(AR, Min), Min >= X, Max < X, checkABB(AL), checkABB(AR).

% Insere item
insertElem(Elem, nil, tree(Elem, nil, nil)).
insertElem(Elem, tree(X, AL, AR), NewTree) :-
  Elem < X,
  insertElem(Elem, AL, NewTree1),
  NewTree = tree(X, NewTree1, AR).
insertElem(Elem, tree(X, AL, AR), NewTree) :-
  insertElem(Elem, AR, NewTree1),
  NewTree = tree(X, AL, NewTree1).

% Remove item
maiorAL(tree(X, A, nil), X, A).
maiorAL(tree(X, AL, AR), Maior, NewAL) :-
  maiorAL(AR, Maior1, NewAL1),
  Maior is Maior1,
  NewAL = tree(X, AL, NewAL1).

deletElem(Elem, tree(Elem, AL, AR), AR) :-
  AL == nil.
deletElem(Elem, tree(Elem, AL, AR), tree(MaiorAL, NewAL, AR)) :-
  maiorAL(AL, MaiorAL, NewAL).
deletElem(Elem, tree(X, AL, AR), NewTree) :-
  Elem < X,
  deletElem(Elem, AL, NewTree1),
  NewTree = tree(X, NewTree1, AR).
deletElem(Elem, tree(X, AL, AR), NewTree) :-
  deletElem(Elem, AR, NewTree1),
  NewTree = tree(X, AL, NewTree1).

% Calcula profundidade máxima Abb
updateDepth(Acc, Acc1, Acc2) :-
    Acc1 > Acc2 -> Acc is Acc1 + 1; Acc is Acc2 + 1.

depthTree(nil, 0).
depthTree(tree(_, AR, AL), Acc) :-
  depthTree(AL, Acc1),
  depthTree(AR, Acc2),
  updateDepth(Acc, Acc1, Acc2).

% Lista infixada
abbToListInfix(nil, []).
abbToListInfix(tree(X, AL, AR), R) :-
  abbToListInfix(AL, RL),
  abbToListInfix(AR, RR),
  append(RL, [X|RR], R).

% Lista prefixada
abbToListPrefix(nil, []).
abbToListPrefix(tree(X, AL, AR), R) :-
  abbToListPrefix(AL, RL),
  abbToListPrefix(AR, RR),
  append(RL, RR, RU),
  R = [X|RU].

% Lista to abb
listToAbb([], nil).
listToAbb([X|XS], NewTree) :- listToAbb(XS, NewTree1), insertElem(X, NewTree1, NewTree).
