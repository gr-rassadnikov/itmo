module HW4.Funcs
  ( Annotated (..)
  , Except (..)
  , mapAnnotated
  , mapExcept
  ) where

import HW4.Types

mapAnnotated :: (a -> b) -> (Annotated e a -> Annotated e b)
mapAnnotated fun (a :# b) = fun a :# b  

mapExcept :: (a -> b) -> (Except e a -> Except e b)
mapExcept fun (Success result) = Success (fun result)
mapExcept _ (Error e)          = Error e
