main :-
  read_string(user_input, _, Input),
  toTrechos(Input, Trechos),
  recursiveTrechos(Trechos, TrechosR),
  print_list(TrechosR).

% prints a list of lists of characters
print_list([]).
print_list([ []|_ ]).
print_list([X|XS]) :-
  atomics_to_string(X, String), % converts a list of characters into a string
  writeln(String),
  print_list(XS).

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
  ((MatchList == []; SegmentsR \= []) ->
    Segments = SegmentsR;
   	append(MatchList, SegmentsR, Segments),
    XR = Xr,
    YR = Yr).

%Get combinations for X element from trechos
getXSegments(_, [], [], _, _).
getXSegments(X, [Y|YS], MatchList, XR, YR) :-
  getXSegments(X, YS, MatchListR, XR, YR),
  (X == Y ->
  	MatchList = MatchListR;
    matchTrecho(X, Y, Segment, 3, 0),
    ((Segment == [-1]; MatchListR \= []) ->
      MatchList = MatchListR;
      MatchList = [Segment|MatchListR],
      XR = X,
      YR = Y)).

% Try to make a Segment unifying two gens
matchTrecho(X, Y, Segment, Acc, AccMax) :-
    length(X, Xlen),
    length(Y, Ylen),
    (Acc =< Ylen, Acc =< Xlen ->
      reverse(X, XRev),
      slice(XRev, 1, Acc, XSlice),
      reverse(XSlice, XRevSlice),
      slice(Y, 1, Acc, YSlice),
   	  (XRevSlice == YSlice ->
          AccMaxP is Acc,
          AccP is Acc + 1,
          matchTrecho(X, Y, Segment, AccP, AccMaxP);
          AccP is Acc + 1,
          AccMaxP is AccMax,
          matchTrecho(X, Y, Segment, AccP, AccMaxP));
      (AccMax >= 4 ->
        length(Y, Ylen),
        AccMaxP is AccMax + 1,
        slice(Y, AccMaxP, Ylen, YEnd),
        append(X, YEnd, Segment);
        Segment = [-1])).
