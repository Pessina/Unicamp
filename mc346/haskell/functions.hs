tam [] = 0
tam x = 1 + tam (tail x)

tam1 x
  | x == [] = 0
  | True = 1 + tam1 (tail x)

soma [x] = x
soma (x:xs) = x + soma xs

somapar [x] = (if mod x 2 == 0 then x else 0)
somapar (x:xs) = (if mod x 2 == 0 then x else 0) + somapar xs

somaidxpar [] = 0
somaidxpar [x] = 0
somaidxpar (x1:x2:xs) = x2 + somaidxpar xs

existeElemento []  elemento = False
existeElemento (x:xs) elemento = if elemento == x then True else existeElemento xs elemento

-- Corrigir
posicaoElemento []  elemento = 0
posicaoElemento (x:xs) elemento = 1 + if elemento == x then 0 else posicaoElemento xs elemento

contaElemento []  elemento = 0
contaElemento (x:xs) elemento = (if elemento == x then 1 else 0) + contaElemento xs elemento

maiorElemento [x] = x
maiorElemento (x1:x2:xs) =  if x1 > x2 then maiorElemento (xs ++ [x1]) else maiorElemento (x2:xs)

-- Panda example
maior [x] = x
maior (x:xs) = if x > maior xs then x else maior xs

trocaVelhoNovo [] v n = []
trocaVelhoNovo (x:xs) v n = (if x == v then n else x) : trocaVelhoNovo xs v n
