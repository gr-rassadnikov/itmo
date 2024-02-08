module HW2.T3
  ( epart
  , mcat
  ) where

mcat :: Monoid a => [Maybe a] -> a
mcat = foldr completion mempty where
  completion :: Monoid a => Maybe a -> a -> a
  completion Nothing list  = list
  completion (Just e) list = e <> list

epart :: (Monoid a, Monoid b) => [Either a b] -> (a, b)
epart = foldr completion (mempty, mempty) where
  completion :: (Monoid a, Monoid b) => Either a b -> (a, b) -> (a, b)
  completion (Right right) (a, b) = (a, right <> b)
  completion (Left left) (a, b)   = (left <> a, b)
