data Tuple = Tuple String String String deriving (Eq, Show, Read)

data Node = Node {
  label :: String,
  list :: [Tuple]
} deriving (Eq, Show, Read)

node = Node  {
  label = "vertix",
  list = [
    (Tuple "end1" "path" "time"),
    (Tuple "end2" "path" "time")
  ]
}

splitListByElement element list =
  foldl (\acc x -> if x == element then ([]:acc) else ((acc!!0 ++ [x]):(tail acc)) ) [[]] list

printNode (Node vertice edges) = print edges

toNode element = Node {
                  label = element!!0,
                  list = [
                    (Tuple (element!!1) (element!!2) (element!!3))
                  ]
                }

insertEdge edge edges = edge:edges

insertNode (Node vertice edge) [] = [(Node vertice edge)]
insertNode (Node vertice edge) ((Node vertice' edge'):xs)
  | vertice == vertice' = (Node vertice (insertEdge (head edge) edge')):xs
  | otherwise = (Node vertice' edge'):(insertNode (Node vertice edge) xs)

createGraph list = foldl (\acc x -> insertNode(toNode x) acc) [] list

main = do
  content <- getContents
  let
    listLines = map words (lines content)
    listSplited = splitListByElement [] listLines
    path = listSplited!!0
    transportPeriods = listSplited!!1
    edges = listSplited!!2
    graph = createGraph edges
  print (graph)
