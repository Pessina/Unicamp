main :-
  prompt(_, ''),
  % read_string(user_input, _, Input),
  toTrechos(
  "xyxyxyaaaaabbbbbbbbcccccccccddddddddefefe1112222222211111122222222ddddddd
ddddddababababababababababababababababab", Trechos),
  writeln(Trechos),
  recursiveTrechos(Trechos, TrechosR),
  printList(TrechosR).

% Print a list
printList([]).
printList([X|XS]) :-
  atom_chars(A, X),
  writeln(A),
  printList(XS).

% Recursive search for new trechos, until no more trechos can be created
recursiveTrechos(Trechos, TrechosR) :-
    getSegments(Trechos, Trechos, Segments, XR, YR),
    (Segments == [] ->
    	TrechosR = Trechos;
    	delete(Trechos, XR, TrechosR1),
    	delete(TrechosR1, YR, TrechosR2),
   		append(Segments, TrechosR2, TrechosR3),
        writeln(TrechosR3),
        recursiveTrechos(TrechosR3, TrechosR)).

% Take the string input, and return list of trechos
toTrechos(Input, Trechos) :-
  atomic_list_concat(TrechosString, '\n', Input),
  maplist(atom_chars, TrechosString, Trechos).

% Take the list of trechos, and return the segments
getSegments([], _, [], _, _).
getSegments([X|XS], Trechos, Segments, XR, YR) :-
  getSegments(XS, Trechos, SegmentsR, XR, YR),
  getXSegments(X, Trechos, MatchList, Xr, Yr),
  ((MatchList == []; SegmentsR \= []) -> % Segments is with element
    Segments = SegmentsR;
   	append(MatchList, SegmentsR, Segments),
    XR = Xr,
    YR = Yr).

getXSegments(_, [], [], _, _).
getXSegments(X, [Y|YS], MatchList, XR, YR) :-
  getXSegments(X, YS, MatchListR, XR, YR),
  (X == Y ->
  	MatchList = MatchListR;
    matchTrecho(X, Y, Segment, 0, Y),
    ((Segment == [-1]; MatchListR \= []) -> % Or segment is with element
      MatchList = MatchListR;
      MatchList = [Segment|MatchListR],
      XR = X,
      YR = Y)).

% Fix matchTrecho error when last characters are the same
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
