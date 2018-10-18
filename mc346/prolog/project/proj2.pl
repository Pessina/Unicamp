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
    length(Trechos, LengthI),
    getSegments(Trechos, Trechos, Segments, XR, YR),
    (var(XR), var(YR) ->
    	TrechosR3 = Trechos;
    	delete(Trechos, XR, TrechosR1),
    	delete(TrechosR1, YR, TrechosR2),
   		append(Segments, TrechosR2, TrechosR3)),
    length(TrechosR3, LengthF),

    (LengthI =\= LengthF ->
      recursiveTrechos(TrechosR3, TrechosR);
      TrechosR = TrechosR3).


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
