data Edge = Edge {
  end :: String,
  transport_or_start :: String,
  time :: String
} deriving (Eq, Show, Read)

data Node = Node {
  label :: String,
  list :: [Edge]
} deriving (Eq, Show, Read)

data DjikstraNode = DjikstraNode {
  node_id :: String,
  d :: Float,
  pai :: String,
  neighbors :: [Edge]
} deriving (Eq, Show, Read)

printNode (Node label edges) = print edges

sumFloatString str flt = flt + read str :: Float

checkSubStr s l = check' s l True where
    check' _ [] h = True
    check' [] _ h = False
    check' (x:xs) (y:ys) h = (y == x && check' xs ys False) || (h && check' xs (y:ys) h)

splitListByElement element list =
  foldl (\acc x -> if x == element then ([]:acc) else ((acc!!0 ++ [x]):(tail acc))) [[]] list

splitListByTransport list =
  foldl (\acc x -> if (x!!2) == "a-pe" then (x:(fst acc),(snd acc))
                  else ((fst acc),x:(snd acc)) ) ([],[]) list

toNodeEdge element = Node {
                      label = element!!0,
                      list = [
                        Edge {
                          end = element!!1,
                          transport_or_start = element!!2,
                          time = element!!3
                        }
                      ]
                    }

toNodeLine element =  Node {
                        label = element!!2,
                        list = [
                          Edge {
                            end = element!!1,
                            transport_or_start = element!!0,
                            time = element!!3
                          }
                        ]
                      }

addEdgeToNode node newNode  = Node (label node) (head (list newNode):list node)

insertNode newNode [] = [newNode]
insertNode newNode (node:xs)
  | (label newNode) == (label node) = (addEdgeToNode node newNode):xs
  | otherwise = node:(insertNode newNode xs)

createGraph list toFunction = foldl (\acc x -> insertNode(toFunction x) acc) [] list

createTransitiveList listNodes = foldl (\acc node -> (createTransitiveLineList node) ++ acc) [] listNodes

createTransitiveLineList node = fst $ createTransitiveLineList' (label node) (list node) where
  createTransitiveLineList' label (x:xs)
    | xs == [] = ([[transport_or_start x, end x, label, time x]], 0)
    | otherwise = foldl (\acc y -> (
        [transport_or_start x, end y, label, show $ sumFloatString (time y) (snd acc)]:(fst acc),
        sumFloatString (time y) (snd acc)
      ))
      (fst $ createTransitiveLineList' label xs, 0) (x:xs)

getHalfBaseTransportTime line transportPeriods = (read $ filter (\x -> line == x!!0) transportPeriods!!0!!1 :: Float) / 2

addBaseTransportTime list  transportPeriods = map (\x -> [x!!0, x!!1, x!!2, show (sumFloatString (x!!3) (getHalfBaseTransportTime (x!!2) transportPeriods))]) list


-------- Remove repeated edges with large weights ----
isOptimalEdge _ [] = True
isOptimalEdge x (e:es) = if (end x == end e) && (toFloat (time x) > toFloat (time e))
                            then False
                            else isOptimalEdge x es

removeLargeWeights edgeList = foldl (\acc x -> if isOptimalEdge x edgeList then x:acc else acc) [] edgeList

trimVertex Node {label=lb, list=ls} = Node {label=lb, list=removeLargeWeights ls}

trimGraph adjacencyList = map trimVertex adjacencyList

toFloat s = read s :: Float
-----------------------------------------------------

------ Add nodes that don't have any edges starting from them --------
belongsToNames [] _ = False
belongsToNames (n:ns) x = if x == n then True else belongsToNames ns x
belongsToGraph [] _ = False
belongsToGraph (v:vs) n = if label v == n then True else belongsToGraph vs n

getNodeNames edges = foldl (\acc x -> (x!!1):acc) [] edges
getUniqueNames names = foldl (\acc x -> if belongsToNames acc x then acc else x:acc) [] names
getUnrepresentedNames graph names = foldl(\acc n -> if belongsToGraph graph n then acc else n:acc) [] names

addRemainingNodes graph edges = foldl (\acc x -> (Node {label=x, list=[]}):acc) graph pending_names
    where names = getNodeNames edges
          unique_names = getUniqueNames names
          pending_names = getUnrepresentedNames graph unique_names

-------- Initialize graph ----------
inf = 1/0
initDjikstra origin [] = []
initDjikstra origin (v:vs) = if label v == origin
                              then DjikstraNode {node_id=origin, d=0, pai="@", neighbors=list v}:initDjikstra origin vs
                              else DjikstraNode {node_id=label v, d=inf, pai="@", neighbors=list v}:initDjikstra origin vs


------- Apply Djikstra -----------------------
-- Util
minNode nodeList = foldl1(\acc n -> if (d n <= d acc) then n else acc) nodeList -- Ideally, we should figure out a way of extracting min considering a negative starting d
popNode node queue = foldl(\acc n -> if node_id n == node_id node then acc else n:acc) [] queue
isNeighbor _ [] = (False, 0)
isNeighbor name (n:ns) = if name == end n then (True, toFloat (time n)) else isNeighbor name ns
belongsToQueue n queue = foldl (\acc q -> if node_id n == node_id q then True else acc) False queue
updateQueue queue graph = foldl (\acc n -> if belongsToQueue n queue then n:acc else acc) [] graph

-- Core
relaxNode p v w DjikstraNode {node_id=name, d=d, pai=pai, neighbors=nbrs} = if (v+w < d) then DjikstraNode {node_id=name, d=(v+w), pai=p, neighbors=nbrs}
                                                                                         else DjikstraNode {node_id=name, d=d, pai=pai, neighbors=nbrs}
relaxNeighbors DjikstraNode {node_id=name, d=value, pai=pai, neighbors=nbrs} graph = foldl (\acc n -> if fst (isNeighbor (node_id n) nbrs)
    then (relaxNode name value (snd (isNeighbor (node_id n) nbrs)) n):acc else n:acc) [] graph
djikstra graph [] = graph
djikstra graph p_queue = djikstra relaxedGraph new_p_queue
    where u = minNode p_queue
          relaxedGraph = relaxNeighbors u graph
          new_p_queue = updateQueue (popNode u p_queue) relaxedGraph

------ Get (String, Cost) tuple from graph --------------

getNode name graph = foldl1 (\acc x -> if node_id x == name then x else acc) graph
getTransportationMode name node = foldl (\acc x -> if name == end x then transport_or_start x else acc) "not found" (neighbors node)

getStringPath _ "@" graph = []
getStringPath name par_name graph = (getStringPath par_name gp_name graph) ++ par_name ++ " " ++ (getTransportationMode name par_node) ++ " "
    where par_node = getNode par_name graph
          gp_name = pai par_node

getTotalTime name graph = d (getNode name graph)
getPath name graph = (getStringPath name par_name graph) ++ name ++ "\n" ++ (show (getTotalTime name graph))
    where node = getNode name graph
          par_name = pai node
-----------------------------------------------------

main = do
  content <- getContents
  let
    listSplitted = splitListByElement [] (map words (lines content))
    path = listSplitted!!0
    transportPeriods = listSplitted!!1
    edges = splitListByTransport (listSplitted!!2)
    edgesAPe = (fst edges)
    edgesTransport = (snd edges)
    listTransport = addBaseTransportTime (createTransitiveList (createGraph edgesTransport toNodeLine)) transportPeriods
    multiGraph = createGraph (edgesAPe ++ listTransport) toNodeEdge

    trimmedGraph = trimGraph  multiGraph
    completeGraph = addRemainingNodes trimmedGraph (listSplitted!!2)
    initGraph = initDjikstra (head (head path)) completeGraph
    djikstraGraph = djikstra initGraph initGraph
    optimalPath = getPath ((head path)!!1) djikstraGraph

  putStrLn(optimalPath)
