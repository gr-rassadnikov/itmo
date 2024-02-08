module HW2.T2
  ( joinWith
  , splitOn
  ) where

import Data.List.NonEmpty (NonEmpty (..))

splitOn :: Eq a => a -> [a] -> NonEmpty [a]
splitOn separator = foldr completion ([] :| []) where
  completion chr (h :| t) =
    if separator == chr
      then [] :| (h : t)
      else (chr : h) :| t


joinWith :: a -> NonEmpty [a] -> [a]
joinWith separator (h :| t) = foldl completion h t where
  completion chr list = chr ++ (separator : list)