module HW0.T5
  ( Nat
  , nFromNatural
  , nmult
  , nplus
  , ns
  , nToNum
  , nz
  ) where

import Numeric.Natural

type Nat a = (a -> a) -> a -> a

nz :: Nat a
nz _ natZ = natZ

ns :: Nat a -> Nat a
ns f natO natI = natO (f natO natI) 

nplus :: Nat a -> Nat a -> Nat a
nplus natL natR f natV = natL f (natR f natV)

nmult :: Nat a -> Nat a -> Nat a
nmult natL natR  = natL . natR

nFromNatural :: Natural -> Nat a
nFromNatural 0 = nz
nFromNatural n = ns (nFromNatural (n - 1))

nToNum :: Num a => Nat a -> a
nToNum nat = nat (+1) 0
