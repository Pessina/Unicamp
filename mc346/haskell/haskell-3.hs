data Tree a = Empty | Node a (Tree a) (Tree a) deriving (Eq, Show, Read)

root1 = Empty
root2 = (Node 5 (Node 3 (Node 2 Empty Empty) (Node 4 Empty Empty)) (Node 7 (Node 6 (Node 0 Empty Empty) Empty) (Node 8 Empty Empty)))
root3 = (Node 10 Empty Empty)
root4 = (Node 1 Empty Empty)

findElement Empty element = False
findElement (Node value tl tr) element
  | value == element = True
  | element < value = findElement tl element
  | element > value  = findElement tr element

addElement Empty element = (Node element Empty Empty)
addElement (Node value tl tr) element
    | element < value = (Node value (addElement tl element) tr)
    | otherwise = (Node value tl (addElement tr element))

checkAbb Empty = True
checkAbb tree = ((maxHeigh tree) - (minHeight tree)) <= 1 where
  minHeight (Node value tl tr)
    | (tl == Empty) || (tr == Empty) = 0
    | otherwise = if (heighTl <= heighTr) then (1 + heighTl) else (1 + heighTr) where
          heighTl = minHeight tl
          heighTr = minHeight tr
  maxHeigh Empty = -1
  maxHeigh (Node value tl tr )
    | (tl == Empty) && (tr == Empty) = 0
    | otherwise = if (heighTl <= heighTr) then (1 + heighTr) else (1 + heighTl) where
          heighTl = maxHeigh tl
          heighTr = maxHeigh tr
