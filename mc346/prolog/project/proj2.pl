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
getSegments([X|XS], Trechos, Segments) :- getSegments(XS, Trechos, SegmentsR), getXSegments(X, Trechos, MatchList), Segments is [MatchList|SegmentsR].

getXSegments(X, [], []).
getXSegments(X, [Y|YS], MatchList) :- getXSegments(X, YS, MatchListR), matchTrecho(X, Y, Segment, 0, YInicio), Segment != [] -> MatchList is [Segment|MatchListR]; MatchListR.

matchTrecho([], YS, Segment, Acc, YInicio) :- Acc >= 4 -> Segment is YS; Segment is false.
matchTrecho([X|XS], [Y|YS], Segment, Acc, YInicio) :- X = Y, Acc is Acc + 1, matchTrecho(XS, YS, SegmentR, Acc), SegmentR = false -> Segment is false; Segment is [X|SegmentR].
matchTrecho([X|XS], [Y|YS], Segment, Acc, YInicio) :- Acc is 0, matchTrecho(XS, YInicio, SegmentR, Acc), SegmentR = false -> Segment is false; Segment is [X|SegmentR].
