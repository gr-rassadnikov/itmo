module HW3.T4
  ( State (..)
  , Prim (..)
  , Expr (..)
  , mapState
  , wrapState
  , joinState
  , modifyState
  , eval
  ) where

import Control.Monad
import HW3.T1

newtype State s a = S { runS :: s -> Annotated s a }

mapState :: (a -> b) -> State s a -> State s b
mapState fun state = S (\s -> mapAnnotated fun (runS state s))

wrapState :: a -> State s a
wrapState a = S (\s -> a :# s)

joinState :: State s (State s a) -> State s a
joinState stateOut = S (\s -> 
  let a :# sIn = runS stateOut s in 
    runS a sIn)

modifyState :: (s -> s) -> State s ()
modifyState fun = S (\s -> () :# fun s)

instance Functor (State s) where
  fmap = mapState

instance Applicative (State s) where
  pure = wrapState

  (<*>) a b = Control.Monad.ap a b

instance Monad (State s) where
  (>>=) m a = joinState (fmap a m)

data Prim a =
    Add a a
  | Sub a a
  | Mul a a
  | Div a a
  | Abs a
  | Sgn a
  deriving Show

data Expr = Val Double | Op (Prim Expr)
  deriving Show

instance Num Expr where
  (+) l r       = Op (Add l r)
  (-) l r       = Op (Sub l r)
  (*) l r       = Op (Mul l r)
  abs e         = Op (Abs e)
  signum e      = Op (Sgn e)
  fromInteger e = Val (fromInteger e)

instance Fractional Expr where
  (/) l r        = Op (Div l r)
  fromRational e = Val (fromRational e)

eval :: Expr -> State [Prim Double] Double
eval (Val result) = return result

eval (Op (Add left right)) = do 
  lRes <- eval left
  rRes <- eval right
  modifyState (\t -> (Add lRes rRes) : t)
  pure (lRes + rRes)

eval (Op (Sub left right)) = do 
  lRes <- eval left
  rRes <- eval right
  modifyState (\t -> (Sub lRes rRes) : t)
  pure (lRes - rRes)

eval (Op (Mul left right)) = do 
  lRes <- eval left
  rRes <- eval right
  modifyState (\t -> (Mul lRes rRes) : t)
  pure (lRes * rRes)

eval (Op (Div left right)) = do 
  lRes <- eval left
  rRes <- eval right
  modifyState (\t -> (Div lRes rRes) : t)
  pure (lRes / rRes)

eval (Op (Abs element)) = do 
  eRes <- eval element
  modifyState (\t -> (Abs eRes) : t)
  pure (abs eRes)

eval (Op (Sgn element)) = do 
  eRes <- eval element
  modifyState (\t -> (Sgn eRes) : t)
  pure (signum eRes)
