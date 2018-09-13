parseListToTuple list = 

main = do
  content <- getContents
  let
    listLines = lines content
    listLinesSplited = map words listLines

  print listLinesSplited
