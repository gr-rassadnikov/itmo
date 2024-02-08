{-# LANGUAGE TypeOperators #-}

module HW0.T1
  ( type (<->) (Iso)
  , assocEither
  , assocPair
  , distrib
  , flipIso
  , runIso
  ) where

data a <-> b = Iso (a -> b) (b -> a)

distrib :: Either a (b, c) -> (Either a b, Either a c)
distrib (Left a)       = (Left a, Left a) 
distrib (Right (b, c)) = (Right b, Right c)

flipIso :: (a <-> b) -> (b <-> a)
flipIso (Iso f s) = Iso s f 

runIso :: (a <-> b) -> (a -> b)
runIso (Iso f _) = f

assocPair :: (a, (b, c)) <-> ((a, b), c)
assocPair  = Iso (\(a, (b, c)) -> ((a, b), c)) (\((a, b), c) -> (a, (b, c)))

assocEither :: Either a (Either b c) <-> Either (Either a b) c
assocEither = Iso convertF convertS

convertF :: Either a (Either b c) -> Either (Either a b) c
convertF (Left a)          = Left (Left a)
convertF (Right (Left b))  = Left (Right b)
convertF (Right (Right c)) = Right c

convertS :: Either (Either a b) c -> Either a (Either b c)
convertS (Left (Left a))  = Left a
convertS (Left (Right b)) = Right (Left b)
convertS (Right c)        = Right (Right c)
