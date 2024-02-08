module HW1.T2
  ( N (..)
  , nplus
  , nmult
  , nsub
  , nFromNatural
  , nToNum
  , ncmp
  , nEven
  , nOdd
  , ndiv
  , nmod
  ) where

import Numeric.Natural

data N = Z | S N
  deriving Show

nplus :: N -> N -> N
nplus n Z     = n
nplus Z m     = m
nplus n (S m) = S $ nplus n m
nplus (S n) m = S $ nplus n m

nmult :: N -> N -> N
nmult _ Z     = Z
nmult Z _     = Z
nmult (S Z) m = m
nmult n (S Z) = n
nmult n (S m) = nplus n $ nmult n m
nmult (S n) m = nplus m $ nmult n m

nsub :: N -> N -> Maybe N
nsub Z Z         = Just Z
nsub Z _         = Nothing
nsub n Z         = Just n
nsub (S n) (S m) = nsub n m

ncmp :: N -> N -> Ordering
ncmp n m = case nsub n m of
  Nothing  -> LT
  Just Z   -> EQ
  Just res -> GT

nFromNatural :: Natural -> N
nFromNatural 0 = Z
nFromNatural n = S $ nFromNatural (n - 1)

nToNum :: Num a => N -> a
nToNum Z     = 0
nToNum (S n) = 1 + nToNum n

nEven :: N -> Bool
nEven = undefined

nOdd :: N -> Bool
nOdd = undefined

ndiv :: N -> N -> N
ndiv = undefined

nmod :: N -> N -> N
nmod = undefined
