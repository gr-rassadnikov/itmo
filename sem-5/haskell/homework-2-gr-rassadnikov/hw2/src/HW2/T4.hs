module HW2.T4
  ( DotString (..)
  , Fun (..)
  , Inclusive (..)
  , ListPlus (..)
  ) where

data ListPlus a = a :+ ListPlus a | Last a
  deriving Show

infixr 5 :+

instance Semigroup (ListPlus a) where
  (<>) (Last l) list = l :+ list
  (<>) (h :+ t) l    = h :+ (t <> l)

data Inclusive a b = This a | That b | Both a b
  deriving Show

instance (Semigroup a, Semigroup b) => Semigroup (Inclusive a b) where
  (<>) (This a) (This b)     = This(a <> b)
  (<>) (This a) (That b)     = Both a b
  (<>) (That a) (This b)     = Both b a
  (<>) (That a) (That b)     = That(a <> b)
  (<>) (Both a b) (Both c d) = Both (a <> c) (b <> d)
  (<>) (Both a b) (This c)   = Both (a <> c) b
  (<>) (Both a b) (That c)   = Both a (b <> c)
  (<>) (This a) (Both b c)   = Both (a <> b) c
  (<>) (That a) (Both b c)   = Both b (a <> c)

newtype DotString = DS String
  deriving Show

instance Semigroup DotString where
  (<>) str (DS "")            = str
  (<>) (DS "") str            = str
  (<>) (DS first) (DS second) = DS(first ++ "." ++ second)

instance Monoid DotString where
  mempty = DS ""

newtype Fun a = F (a -> a)

instance Semigroup (Fun a) where
  (<>) (F first) (F second) = F $ first . second

instance Monoid (Fun a) where
  mempty = F id
