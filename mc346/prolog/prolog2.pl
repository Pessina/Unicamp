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

checkABB(tree(X, nil, nil), true).
checkABB(tree(X, AL, AR), P) :- getMaxTree(AL, Max), Max < X, getMinTree(AR, Min), Min >= X,  checkABB(AL, P), checkABB(AR, P).
checkABB(tree(X, AL, AR), false).
