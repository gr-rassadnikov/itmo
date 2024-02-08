module HW3.T2
  ( distOption
  , wrapOption
  , distPair
  , wrapPair
  , distQuad
  , wrapQuad
  , distAnnotated
  , wrapAnnotated
  , distExcept
  , wrapExcept
  , distPrioritised
  , wrapPrioritised
  , distStream
  , wrapStream
  , distList
  , wrapList
  , distFun
  , wrapFun
  , mergeTwoLists
  ) where

import HW3.T1

distOption :: (Option a, Option b) -> Option (a, b)
distOption (Some a, Some b) = Some (a, b)
distOption _                = None

wrapOption :: a -> Option a
wrapOption = Some 

distPair :: (Pair a, Pair b) -> Pair (a, b)
distPair (P aF aS, P bF bS) = P (aF, bF) (aS, bS)

wrapPair :: a -> Pair a
wrapPair a = P a a

distQuad :: (Quad a, Quad b) -> Quad (a, b)
distQuad (Q aF aS aT aQ, Q bF bS bT bQ) = Q (aF, bF) (aS, bS) (aT, bT) (aQ, bQ) 

wrapQuad :: a -> Quad a
wrapQuad a = Q a a a a

distAnnotated :: Semigroup e => (Annotated e a, Annotated e b) -> Annotated e (a, b)
distAnnotated (a :# e1, b :# e2) = (a, b) :# (e1 <> e2) 

wrapAnnotated :: Monoid e => a -> Annotated e a
wrapAnnotated a = a :# mempty

distExcept :: (Except e a, Except e b) -> Except e (a, b)
distExcept (Error a, _)           = Error a
distExcept (_, Error b)           = Error b
distExcept (Success a, Success b) = Success (a, b)

wrapExcept :: a -> Except e a
wrapExcept = Success

distPrioritised :: (Prioritised a, Prioritised b) -> Prioritised (a, b)
distPrioritised (Low a, Low b) = Low (a, b)
distPrioritised (Low a, Medium b) = Medium (a, b)
distPrioritised (Low a, High b) = High (a, b)
distPrioritised (Medium a, Low b) = Medium (a, b)
distPrioritised (Medium a, Medium b) = Medium (a, b)
distPrioritised (Medium a, High b) = High (a, b)
distPrioritised (High a, Low b) = High (a, b)
distPrioritised (High a, Medium b) = High (a, b)
distPrioritised (High a, High b) = High (a, b)

wrapPrioritised :: a -> Prioritised a
wrapPrioritised = Low

distStream :: (Stream a, Stream b) -> Stream (a, b)
distStream (aH :> aT, bH :> bT) = (aH, bH) :> distStream (aT, bT)

wrapStream :: a -> Stream a
wrapStream a = a :> wrapStream a

mergeTwoLists :: List a -> List a -> List a
mergeTwoLists Nil b      = b
mergeTwoLists (h :. t) s = h :. mergeTwoLists t s

distListUnivariate :: (List a, List b) -> List (a, b)
distListUnivariate (Nil,  _)            = Nil
distListUnivariate (_, Nil)             = Nil
distListUnivariate (aH :. aT, bH :. bT) = (aH, bH) :. distListUnivariate (aH :. aT, bT)

distList :: (List a, List b) -> List (a, b)
distList (Nil,  _)            = Nil
distList (_, Nil)             = Nil
distList (aH :. aT, b) = mergeTwoLists (distListUnivariate (aH :. aT, b)) (distList(aT, b))

wrapList :: a -> List a
wrapList a = a :. Nil

distFun :: (Fun i a, Fun i b) -> Fun i (a, b)
distFun (F a, F b) = F (\i -> (a i , b i))

wrapFun :: a -> Fun i a
wrapFun a = F (const a)
