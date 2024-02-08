module HW2.T1
  ( Tree (..)
  , tfoldr
  ) where

data Tree a = Leaf | Branch !Int (Tree a) a (Tree a)
  deriving (Show)

tfoldr :: (a -> b -> b) -> b -> Tree a -> b
tfoldr _ value Leaf                       = value
tfoldr callback value (Branch _ l node r) = tfoldr callback (callback node (tfoldr callback value r)) l
