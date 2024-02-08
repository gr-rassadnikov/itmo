module HW1.T3
  ( Tree (..)
  , tsize
  , tdepth
  , tmember
  , tinsert
  , tFromList
  , tfoldr
  , treeToList
  ) where

type Meta = Int

data Tree a = Leaf | Branch Meta (Tree a) a (Tree a)

tsize :: Tree a -> Int
tsize Leaf                = 0
tsize (Branch size _ _ _) = size

tdepth :: Tree a -> Int
tdepth Leaf             = 0
tdepth (Branch _ l _ r) = (+) 1 $ max (tdepth l) (tdepth r)

tmember :: Ord a => a -> Tree a -> Bool
tmember _ Leaf = False
tmember e (Branch _ l value r) = case compare e value of
  LT -> tmember e l
  GT -> tmember e r
  EQ -> True

tinsertNew :: Ord a => a -> Tree a -> Tree a
tinsertNew value Leaf = (Branch 1 Leaf value Leaf)
tinsertNew e (Branch size l value r) = case compare e value of
   LT -> Branch (size + 1) (tinsertNew e l) value r
   GT -> Branch (size + 1) l value (tinsertNew e r)
   EQ -> (Branch size l value r)

tinsert :: Ord a => a -> Tree a -> Tree a
tinsert e tree = if tmember e tree then tree else tinsertNew e tree

tFromList :: Ord a => [a] -> Tree a
tFromList list = case list of
  (head :tail) -> tinsert head $ tFromList tail
  []           -> Leaf


tfoldr :: (a -> b -> b) -> b -> Tree a -> b
tfoldr _ value Leaf               = value
tfoldr callback value (Branch size l node r) = tfoldr callback (callback node (tfoldr callback value r)) l

treeToList = tfoldr (:) []