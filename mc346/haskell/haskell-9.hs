add l = l ++ "olar"

main = do
  putStrLn "input caracter"
  name <- getLine
  add name
  putStrLn (name)
