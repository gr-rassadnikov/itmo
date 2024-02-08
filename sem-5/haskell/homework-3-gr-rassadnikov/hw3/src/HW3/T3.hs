module HW3.T3
  ( joinOption
  , joinExcept
  , joinAnnotated
  , joinList
  , joinFun
  ) where

import HW3.T1 (Fun(F), List (Nil, (:.)), Except(Error, Success), Option(None, Some), Annotated ((:#)))
import HW3.T2 (mergeTwoLists)

joinOption :: Option (Option a) -> Option a
joinOption None     = None
joinOption (Some a) = a

joinExcept :: Except e (Except e a) -> Except e a
joinExcept (Error e)        = Error e
joinExcept (Success result) = result

joinAnnotated :: Semigroup e => Annotated e (Annotated e a) -> Annotated e a
joinAnnotated ((a :# eInn) :# eOut) = a :# (eOut <> eInn)

joinList :: List (List a) -> List a
joinList Nil      = Nil
joinList (h :. t) = mergeTwoLists h (joinList t)

unwrapFun :: Fun i a -> i -> a
unwrapFun (F a) = a

joinFun :: Fun i (Fun i a) -> Fun i a
joinFun (F a) = F (\i -> unwrapFun (a i) i)
 