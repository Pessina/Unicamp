main :-
  prompt(_, ''),
  % read_string(user_input, _, Input),
  toTrechos(
  "xxxxxababababyyyyyy
yyyyyyeeeeeeeeeeeeee", Trechos),
  getSegments(Trechos, Trechos, Segments),

 printList(Segments).


% Print a list
printList([]).
printList([X|XS]) :-
  % writeln(user_output, X),
  writeln(X),
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

getXSegments(_, [], []).
getXSegments(X, [Y|YS], MatchList) :-
  getXSegments(X, YS, MatchListR),
  write(X),
  writeln(Y),
  matchTrecho(X, Y, Segment, 0, Y),
  compare(=, SegmentR, [-1]) ->
    MatchList = MatchListR;
	MatchList = [Segment|MatchListR].

matchTrecho([], YS, Segment, Acc, _) :-
  Acc >= 4 ->
    Segment = YS;
    Segment = [-1].
matchTrecho([X|XS], [Y|YS], Segment, Acc, YInicio) :-
  X == Y,
  AccP is Acc + 1,
  matchTrecho(XS, YS, SegmentR, AccP, YInicio),
  write(X),
  write(" "),
  write(SegmentR),
  write(" "),
  writeln([X|SegmentR]),
  compare(=, SegmentR, [-1]) ->
   	Segment = [-1];
    Segment = [X|SegmentR].
matchTrecho([X|XS], _, Segment, _, YInicio) :-
  AccP is 0,
  matchTrecho(XS, YInicio, SegmentR, AccP, YInicio),
  compare(=, SegmentR, [-1]) ->
    Segment = [-1];
    Segment = [X|SegmentR].
