main :-
  prompt(_, ''),
  % read_string(user_input, _, Input),
  toTrechos(
  "xyxyxyaaaaabbbbbbbbcccccccccddddddddefefe1112222222211111122222222ddddddd
dddddddababababababababababababababababab", Trechos),
  recursiveTrechos(Trechos, TrechosR),
  printList(TrechosR).

% Print a list
printList([]).
printList([X|XS]) :-
  atom_chars(A, X),
  writeln(A),
  printList(XS).

% Slice a list
slice([X|_],1,1,[X]).
slice([X|Xs],1,K,[X|Ys]) :- K > 1,
   K1 is K - 1, slice(Xs,1,K1,Ys).
slice([_|Xs],I,K,Ys) :- I > 1,
   I1 is I - 1, K1 is K - 1, slice(Xs,I1,K1,Ys).

% Recursive search for new trechos, until no more trechos can be created
recursiveTrechos(Trechos, TrechosR) :-
    getSegments(Trechos, Trechos, Segments, XR, YR),
    (Segments == [] ->
    	TrechosR = Trechos;
    	delete(Trechos, XR, TrechosR1),
    	delete(TrechosR1, YR, TrechosR2),
   		append(Segments, TrechosR2, TrechosR3),
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
    matchTrecho(X, Y, Segment, 3),
    ((Segment == [-1]; MatchListR \= []) -> % Or segment is with element
      MatchList = MatchListR;
      MatchList = [Segment|MatchListR],
      XR = X,
      YR = Y)).

matchTrecho(X, Y, Segment, Acc) :-
    reverse(X, XRev),
    slice(XRev, 1, Acc, XSlice),
    reverse(XSlice, XRevSlice),
    slice(Y, 1, Acc, YSlice),
    (XRevSlice == YSlice ->
    	AccP is Acc + 1,
    	matchTrecho(X, Y, Segment, AccP);
    	(Acc >= 4 ->
        	length(Y, Ylen),
        	slice(Y, Acc, Ylen, YEnd),
        	append(X, YEnd, Segment);
        	Segment = [-1])).










    
