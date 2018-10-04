countElement element xs = foldl (\acc x -> if x == element then acc+1 else acc) 0 xs

countElementFunc f xs = foldl (\acc x -> if f x then acc+1 else acc) 0 xs

trocaVelhoNovo xs velho novo = map (\x -> if x == velho then novo else x) xs

removeElemento element xs = filter (\x -> x /= element) xs
