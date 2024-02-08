{-# LANGUAGE DerivingStrategies #-}
{-# LANGUAGE GeneralisedNewtypeDeriving #-}

module HW4.T2
  ( ParseError (..)
  , runP
  , pChar
  , parseError
  , parseIntExpr
  ) where

import Numeric.Natural (Natural)
import Control.Applicative
import Control.Monad

-- 
import Data.Char (digitToInt, isDigit, isSpace, isUpper)
-- 

import HW4.Types
import HW4.T1 (ExceptState(..))

data ParseError = ErrorAtPos Natural
  deriving Show

newtype Parser a = P (ExceptState ParseError (Natural, String) a)
  deriving newtype (Functor, Applicative, Monad)

runP :: Parser a -> String -> Except ParseError a
runP (P p) str = case runES p (0, str) of
  Success (h :# _) -> Success h
  Error e          -> Error e               

-- Just an example of parser that may be useful
-- in the implementation of 'parseExpr'
pChar :: Parser Char
pChar = P $ ES $ \(pos, s) ->
  case s of
    []     -> Error (ErrorAtPos pos)
    (c:cs) -> Success (c :# (pos + 1, cs))

parseError :: Parser a
parseError = P (ES (\(pos, _) -> Error (ErrorAtPos pos)))

instance Alternative Parser where
  empty = parseError

  (<|>) (P eStL) (P eStR) = P (ES (\(pos, str) -> 
    case runES eStL (pos, str) of
     Success (h :# t) -> Success (h :# t)
     Error _          -> runES eStR (pos, str)
    ))
    

-- No metohds
instance MonadPlus Parser

-- parseExpr :: String -> Except ParseError Expr
-- parseExpr = undefiend

parseIntExpr :: String -> Except ParseError Integer
parseIntExpr = runP expr


pCharEq :: Char -> Parser Char
pCharEq c = mfilter (c ==) pChar

-- Convert @String@ to @Integer@
strToInt :: String -> Integer
strToInt = foldl (\ acc c -> toInteger (digitToInt c) + 10 * acc) 0

pStrInt :: Parser String
pStrInt = some (mfilter isDigit pChar)

pInteger :: Parser Integer
pInteger = do
  x <- pStrInt    
  pure $ strToInt (x)


expr = do x <- term
          res <- (pCharEq '+' <|> pCharEq '-')
          y <- expr
          case res of
            '+' -> return(x+y)
            '-' -> return (x-y)
        <|> term

term = do x <- factor
          res <- (pCharEq '*' <|> pCharEq '/')

          y <- term
          case res of
            '*' -> return(x*y)
            '/' -> return (x+y)
        <|> factor

factor = do pCharEq '('
            x <- expr
            pCharEq ')'
            return x
          <|> pInteger