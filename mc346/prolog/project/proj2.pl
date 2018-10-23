% University of Campinas - MC346
% Project 2
% Authors:
% Felipe Sousa Pessina, RA: 171214
% Guilherme Mendeleh Perrotta, RA: 173846

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

% Takes the input, and returns list of trechos
toTrechos(Input, Trechos) :-
  atomic_list_concat(TrechosString, '\n', Input),
  maplist(atom_chars, TrechosString, Trechos).

% Slice a list
slice([X|_],1,1,[X]).
slice([X|Xs],1,K,[X|Ys]) :-
  K > 1,
  K1 is K - 1,
  slice(Xs,1,K1,Ys).
slice([_|Xs],I,K,Ys) :-
  I > 1,
  I1 is I - 1,
  K1 is K - 1,
  slice(Xs,I1,K1,Ys).

% Recursive search for new trechos, until no more trechos can be created
recursiveTrechos(Trechos, TrechosR) :-
    getSegments(Trechos, Trechos, Segments, XR, YR),
    % Check if Segments is empty, if yes stops the recursion
    (Segments == [] ->
    	TrechosR = Trechos;
      % Remove used trechos, and add segment
    	delete(Trechos, XR, TrechosR1),
    	delete(TrechosR1, YR, TrechosR2),
   		append(Segments, TrechosR2, TrechosR3),
      recursiveTrechos(TrechosR3, TrechosR)).

% Take the list of trechos, and return the segments
getSegments([], _, [], _, _).
getSegments([X|XS], Trechos, Segments, XR, YR) :-
  getSegments(XS, Trechos, SegmentsR, XR, YR),
  getXSegments(X, Trechos, MatchList, Xr, Yr),
  % If X matched with some trecho and its the first Segment, add to list. Else just return
  ((MatchList == []; SegmentsR \= []) ->
    Segments = SegmentsR;
   	append(MatchList, SegmentsR, Segments),
    XR = Xr,
    YR = Yr).

% Try to combine X with some other Trechos
getXSegments(_, [], [], _, _).
getXSegments(X, [Y|YS], MatchList, XR, YR) :-
  getXSegments(X, YS, MatchListR, XR, YR),
  % If elements are the same, just skip
  (X == Y ->
  	MatchList = MatchListR;
    matchTrecho(X, Y, Segment, 3, 0),
    % If X match with Y, and the match list is empty add segment to list, set XR and YR matched elements. Else just return
    ((Segment == [-1]; MatchListR \= []) ->
      MatchList = MatchListR;
      MatchList = [Segment|MatchListR],
      XR = X,
      YR = Y)).

% Recursive try to find the greates match between X and Y, slicing the lists
matchTrecho(X, Y, Segment, Acc, AccMax) :-
    length(X, Xlen),
    length(Y, Ylen),
    % Check if the slice is not greater than the lists
    (Acc =< Ylen, Acc =< Xlen ->
      % Reverse the list and get the end X
      reverse(X, XRev),
      slice(XRev, 1, Acc, XSlice),
      reverse(XSlice, XRevSlice),
      % Get the beggining of Y
      slice(Y, 1, Acc, YSlice),
      % Check if the end of X is equal to beggining of Y
   	  (XRevSlice == YSlice ->
          AccMaxP is Acc,
          AccP is Acc + 1,
          matchTrecho(X, Y, Segment, AccP, AccMaxP);
          AccP is Acc + 1,
          AccMaxP is AccMax,
          matchTrecho(X, Y, Segment, AccP, AccMaxP));
      % At the end of recursion, slice the trechos, and combine then by the greatest intersection
      (AccMax >= 4 ->
        length(Y, Ylen),
        AccMaxP is AccMax + 1,
        slice(Y, AccMaxP, Ylen, YEnd),
        append(X, YEnd, Segment);
        Segment = [-1])).
