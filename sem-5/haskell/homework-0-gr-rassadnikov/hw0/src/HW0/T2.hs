module HW0.T2
  ( Not
  , doubleNeg
  , reduceTripleNeg
  ) where

import Data.Void (Void)

type Not a = a -> Void

doubleNeg :: a -> Not (Not a)
doubleNeg a nt = nt a

reduceTripleNeg :: Not (Not (Not a)) -> Not a
reduceTripleNeg nt a = nt (doubleNeg a)
