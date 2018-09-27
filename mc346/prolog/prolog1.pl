% Creating a fact
casado(alberto, tereza).

% Creating a rule
% X is mortal if its human
mortal(X) :- human(X).
human(socrates).

% Recursion
on_route(rome).

on_route(Place):-
  move(Place,Method,NewPlace),
  on_route(NewPlace).

move(home,taxi,halifax).
move(halifax,train,gatwick).
move(gatwick,plane,rome).

% List

% Size of a list
size([], 0).
size([A|B], Count) :- size(B, Count1), Count is Count1 + 1.

% Sum of list elements
sum([], 0).
sum([A|B], Sum) :- sum(B, Sum1), Sum is A + Sum1.

% Sum of even elements of a list
sumEven([], 0).
sumEven([A|B], Sum) :- Even is A mod 2, Even = 0, sumEven(B, Sum1), Sum is A + Sum1.
sumEven([A|B], Sum) :- sumEven(B, Sum1), Sum is Sum1.

% Sum of element in index even
sumEvenIndex([], A, 0).
sumEvenIndex([H|T], A, Sum) :- Even is A mod 2, Even = 0, A1 is A + 1, sumEvenIndex(T, A1, Sum1), Sum is Sum1 + H.
sumEvenIndex([H|T], A, Sum) :- A1 is A + 1, sumEvenIndex(T, A1, Sum1), Sum is Sum1.

% Check if element is on List
check(X, [X|T]).
check(Item, [X|T]) :- check(Item, T).

% Index os element on list
posItem(H, [H|T], 1).
posItem(Item, [H|T], Acc) :- posItem(Item, T, Acc1), Acc is Acc1 + 1.

% Count element on list
countElement([], 0, E).
countElement([H|T], Count, Element) :- Element = H, countElement(T, Count1, Element), Count is Count1 + 1.
countElement([H|T], Count, Element) :- countElement(T, Count1, Element), Count is Count1.





















%
