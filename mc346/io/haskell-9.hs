add2 n = n + 2
mult2 n  = n * 2

main = do
  input <- getLine
  let
    var = (read input :: Int)
    mult = mult2 var
    add = add2 mult
  print ("olar " ++ (add :: String) ++ " olar")
