module HW4.T1
  ( EvaluationError (..)
  , ExceptState (..)
  , mapExceptState
  , wrapExceptState
  , joinExceptState
  , modifyExceptState
  , throwExceptState
  , eval
  ) where

import Control.Monad
import HW4.Types
import HW4.Funcs

data ExceptState e s a = ES { runES :: s -> Except e (Annotated s a) }

mapExceptState :: (a -> b) -> ExceptState e s a -> ExceptState e s b
mapExceptState fun eState = ES (\s -> mapExcept (mapAnnotated fun) (runES eState s))

wrapExceptState :: a -> ExceptState e s a
wrapExceptState a = ES (\s -> Success (a :# s))

joinExceptState :: ExceptState e s (ExceptState e s a) -> ExceptState e s a
joinExceptState stateOut = ES (\s ->
  case runES stateOut s of
    Success (a :# sIn) -> runES a sIn
    Error e            -> Error e
  )

modifyExceptState :: (s -> s) -> ExceptState e s ()
modifyExceptState fun = ES (\s -> Success (() :# fun s))

throwExceptState :: e -> ExceptState e s a
throwExceptState e = ES (\_ -> Error e)

instance Functor (ExceptState e s) where
  fmap = mapExceptState

instance Applicative (ExceptState e s) where
  pure = wrapExceptState
  (<*>) a b = Control.Monad.ap a b

instance Monad (ExceptState e s) where
  (>>=) m a = joinExceptState (fmap a m)

data EvaluationError = DivideByZero
  deriving Show

eval :: Expr -> ExceptState EvaluationError [Prim Double] Double
eval (Val result) = return result

eval (Op (Add left right)) = do 
  lRes <- eval left
  rRes <- eval right
  modifyExceptState (\t -> (Add lRes rRes) : t)
  pure (lRes + rRes)

eval (Op (Sub left right)) = do 
  lRes <- eval left
  rRes <- eval right
  modifyExceptState (\t -> (Sub lRes rRes) : t)
  pure (lRes - rRes)

eval (Op (Mul left right)) = do 
  lRes <- eval left
  rRes <- eval right
  modifyExceptState (\t -> (Mul lRes rRes) : t)
  pure (lRes * rRes)

eval (Op (Div left right)) = do 
  lRes <- eval left
  rRes <- eval right
  case rRes of
    0 -> throwExceptState DivideByZero
    _ -> modifyExceptState (\t -> (Div lRes rRes) : t)
  pure (lRes / rRes)

eval (Op (Abs element)) = do 
  eRes <- eval element
  modifyExceptState (\t -> (Abs eRes) : t)
  pure (abs eRes)

eval (Op (Sgn element)) = do 
  eRes <- eval element
  modifyExceptState (\t -> (Sgn eRes) : t)
  pure (signum eRes)