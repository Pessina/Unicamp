
pos element l = pos' element l 1 where
  pos' element [] acc = []
  pos' element (x:xs) acc = if x == element
    then acc:pos' element xs (acc+1)
    else pos' element xs (acc+1)

split l e  = [(lista1 l e)] ++ [(lista2 l e)] where
  lista1 (x:xs) e
    | x == e = []
    | otherwise = x:lista1 xs e
  lista2 (x:xs) e
    | x == e = xs
    | otherwise = lista2 xs e

splitall [] e = []
splitall l e = [(lista1 l e)] ++ splitall (lista2 l e) e where
  lista1 (x:xs) e
    | x == e = []
    | otherwise = x:lista1 xs e
  lista2 (x:xs) e
    | x == e = xs
    | otherwise = lista2 xs e

dropn l n = dropn' l n 1 where
  dropn' [] n acc = []
  dropn' (x:xs) n acc = if acc < n then (dropn' xs n (acc+1)) else xs

taken l n = taken' l n 0 where
  taken' [] n acc = []
  taken' (x:xs) n acc = if acc < n then x:(taken' xs n (acc+1)) else []
