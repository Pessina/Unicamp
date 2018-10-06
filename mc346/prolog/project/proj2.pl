main :-
  prompt(_, ''),
  read_string(user_input, _, Input),
  toTrechos(Input, Trechos),
  getSegments(Trechos, Segments),

  printList(Trechos),
  halt.

% Print a list
printList([]).
printList([X|XS]) :- writeln(user_output, X), printList(XS).

% Take the string input, and return list of trechos
toTrechos(Input, Trechos) :- atomic_list_concat(TrechosString, '\n', Input),  maplist(atom_chars, TrechosString, Trechos).

% Take the list of trechos, and return the segments
getSegments([], _, []).
getSegments([X|XS], Trechos, Segments) :- getSegments(XS, Trechos, SegmentsR), matchTrecho(X, Trechos, MatchList), Segments is [MatchList|SegmentsR].

matchTrecho(X, [], []).
matchTrecho
