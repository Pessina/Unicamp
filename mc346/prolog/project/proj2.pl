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
  writeln(Segments).
  %printList(Segments).


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
  (MatchList == [] ->
    Segments = [X|SegmentsR];
   	append(MatchList, SegmentsR, Segments)).

getXSegments(_, [], []).
getXSegments(X, [Y|YS], MatchList) :-
  getXSegments(X, YS, MatchListR),
  (X == Y ->
  	MatchList = MatchListR;
    matchTrecho(X, Y, Segment, 0, Y),
    (Segment == [-1] ->
      MatchList = MatchListR;
      MatchList = [Segment|MatchListR])).

matchTrecho([], YS, Segment, Acc, _) :-
  Acc >= 4 ->
    Segment = YS;
    Segment = [-1].
matchTrecho([X|XS], [Y|YS], Segment, Acc, YInicio) :-
  X == Y,
  AccP is Acc + 1,
  matchTrecho(XS, YS, SegmentR, AccP, YInicio),
  (SegmentR == [-1] ->
   	Segment = [-1];
    Segment = [X|SegmentR]).
matchTrecho([X|XS], _, Segment, _, YInicio) :-
  AccP is 0,
  matchTrecho(XS, YInicio, SegmentR, AccP, YInicio),
 (SegmentR == [-1] ->
   	Segment = [-1];
    Segment = [X|SegmentR]).
