main :-
  prompt(_, ''),
  % read_string(user_input, _, Input),
  toTrechos(
  "xxxxxababababyyyyyy
yyaaaaaaaaaaa
yyyyyyeeeeeeeeeeeeee
cccccccccccccccxxxxx
fffffffffffffffwwwwww
wwwwwwgggggggggggxx", Trechos),
  getSegments(Trechos, Trechos, Segments),

  printList(Trechos).

% Print a list
printList([]).
printList([X|XS]) :-
  writeln(user_output, X),
  printList(XS).

% Take the string input, and return list of trechos
toTrechos(Input, Trechos) :-
  atomic_list_concat(TrechosString, '\n', Input),
  maplist(atom_chars, TrechosString, Trechos).

% Take the list of trechos, and return the segments
getSegments([], _, []).
getSegments([X|XS], Trechos, Segments) :-
  getSegments(XS, Trechos, SegmentsR),
  getXSegments(X, Trechos, MatchList),
  Segments = [MatchList|SegmentsR].

getXSegments(X, [], []).
getXSegments(X, [Y|YS], MatchList) :-
  getXSegments(X, YS, MatchListR),
  matchTrecho(X, Y, Segment, 0, Y),
  Segment != [-1] ->
    MatchList = [Segment|MatchListR];
    MatchList = MatchListR.

matchTrecho([], YS, Segment, Acc, YInicio) :-
  Acc >= 4 ->
    Segment = YS;
    Segment = [-1].
matchTrecho([X|XS], [Y|YS], Segment, Acc, YInicio) :-
  X = Y,
  Acc is Acc + 1,
  matchTrecho(XS, YS, SegmentR, Acc, YInicio),
  SegmentR == [-1] ->
    Segment = [-1];
    Segment = [X|SegmentR].
matchTrecho([X|XS], [Y|YS], Segment, Acc, YInicio) :-
  Acc is 0,
  matchTrecho(XS, YInicio, SegmentR, Acc, YInicio),
  SegmentR == [-1] ->
    Segment = [-1];
    Segment = [X|SegmentR].
