module HW0.T4
  ( fac
  , fib
  , map'
  , repeat'
  ) where

import Numeric.Natural (Natural)
import Data.Function (fix)

repeat' :: a -> [a]
repeat' = fix . (:)

map' :: (a -> b) -> [a] -> [b]
map' = fix mapRec
  where
    mapRec :: ((a -> b) -> [a] -> [b]) -> (a -> b) -> [a] -> [b]
    mapRec _ _ [] = []
    mapRec f mapper (h : t) = mapper h : f mapper t

fib :: Natural -> Natural
fib = fix fibRec
  where
    fibRec :: (Natural -> Natural) -> Natural -> Natural
    fibRec f n
      | n == 0 || n == 1 = 1
      | even n           = f1 * (f1 + 2 * f2)
      | mod n 4 == 1     = (2 * f1 + f2) * (2 * f1 - f2) + 2
      | otherwise        = (2 * f1 + f2) * (2 * f1 - f2) - 2
      where 
        k = div n 2
        f1 = f k
        f2 = f (k - 1)

fac :: Natural -> Natural
fac = fix facRec
  where
    facRec :: (Natural -> Natural) -> Natural -> Natural
    facRec f n
      | n > 1 = n * f (n-1)
      | otherwise = 1
