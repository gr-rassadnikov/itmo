module HW5.Evaluator (eval) where

import HW5.Base
import Control.Monad (when)
import Control.Monad.Trans.Except (ExceptT, runExceptT, throwE)
import qualified Data.Text as T
import Data.Semigroup (stimes)
import Data.Ratio (denominator, numerator)

eval :: Monad m => HiExpr -> m (Either HiError HiValue)
eval expr = runExceptT (evalWithExcept expr)

evalWithExcept :: Monad m => HiExpr -> ExceptT HiError m HiValue
evalWithExcept (HiExprValue val)      = return val
evalWithExcept (HiExprApply fun args) = evalWithArgs fun args

evalWithArgs :: Monad m => HiExpr -> [HiExpr] -> ExceptT HiError m HiValue
evalWithArgs expr [e] = do
                        evalExpr <- evalWithExcept expr
                        arity <- getArity evalExpr
                        when (not (1 `elem` arity)) (throwE HiErrorArityMismatch)
                        evalE <- evalWithExcept e
                        apllyMain evalExpr [evalE]
evalWithArgs expr [e1, e2] = do
                        evalExpr <- evalWithExcept expr
                        arity <- getArity evalExpr
                        when (not (2 `elem` arity)) (throwE HiErrorArityMismatch)
                        evalL <- evalWithExcept e1
                        evalR <- evalWithExcept e2
                        apllyMain evalExpr [evalL, evalR]
evalWithArgs expr [e1, e2, e3] = do
                        evalExpr <- evalWithExcept expr
                        arity <- getArity evalExpr
                        when (not (3 `elem` arity)) (throwE HiErrorArityMismatch)
                        evalE1 <- evalWithExcept e1
                        evalE2 <- evalWithExcept e2
                        evalE3 <- evalWithExcept e3
                        apllyMain evalExpr [evalE1, evalE2, evalE3]
evalWithArgs _ _ = throwE HiErrorArityMismatch

getArity :: Monad m => HiValue -> ExceptT HiError m [Integer]
getArity (HiValueFunction fun) = return $ case fun of
  HiFunDiv -> [2]
  HiFunMul -> [2]
  HiFunAdd -> [2]
  HiFunSub -> [2]
  HiFunNot -> [1]
  HiFunAnd -> [2]
  HiFunOr -> [2]
  HiFunLessThan -> [2]
  HiFunGreaterThan -> [2]
  HiFunEquals -> [2]
  HiFunNotLessThan -> [2]
  HiFunNotGreaterThan -> [2]
  HiFunNotEquals -> [2]
  HiFunIf -> [3]
  HiFunLength -> [1]
  HiFunToUpper -> [1]
  HiFunToLower -> [1]
  HiFunReverse -> [1]
  HiFunTrim -> [1]
getArity (HiValueString _) = return [1,2]
getArity _  = throwE HiErrorInvalidFunction

apllyMain :: Monad m => HiValue  -> [HiValue] -> ExceptT HiError m HiValue
apllyMain (HiValueFunction HiFunAdd) [HiValueNumber e1, HiValueNumber e2] = return $ HiValueNumber (e1 + e2)
apllyMain (HiValueFunction HiFunSub) [HiValueNumber e1, HiValueNumber e2] = return $ HiValueNumber (e1 - e2)
apllyMain (HiValueFunction HiFunMul) [HiValueNumber e1, HiValueNumber e2] = return $ HiValueNumber (e1 * e2)
apllyMain (HiValueFunction HiFunDiv) [HiValueNumber _, HiValueNumber 0]   = throwE HiErrorDivideByZero
apllyMain (HiValueFunction HiFunDiv) [HiValueNumber e1, HiValueNumber e2] = return $ HiValueNumber (e1 / e2)
apllyMain (HiValueFunction HiFunAnd) [HiValueBool e1, HiValueBool e2]     = return $ HiValueBool (e1 && e2)
apllyMain (HiValueFunction HiFunOr)  [HiValueBool e1, HiValueBool e2]     = return $ HiValueBool (e1 || e2)
apllyMain (HiValueFunction HiFunEquals)         [e1, e2]                  = return $ HiValueBool (e1 == e2)
apllyMain (HiValueFunction HiFunNotEquals)      [e1, e2]                  = return $ HiValueBool (e1 /= e2)
apllyMain (HiValueFunction HiFunLessThan)       [e1, e2]                  = return $ HiValueBool (e1 < e2)
apllyMain (HiValueFunction HiFunNotLessThan)    [e1, e2]                  = return $ HiValueBool (e1 >= e2)
apllyMain (HiValueFunction HiFunGreaterThan)    [e1, e2]                  = return $ HiValueBool (e1 > e2)
apllyMain (HiValueFunction HiFunNotGreaterThan) [e1, e2]                  = return $ HiValueBool (e1 <= e2)
apllyMain (HiValueFunction HiFunNot) [HiValueBool e]                      = return $ HiValueBool (not e)
apllyMain (HiValueFunction HiFunIf) [HiValueBool e1, e2, e3]              = return $ if e1 then e2 else e3
apllyMain (HiValueFunction HiFunLength) [HiValueString e]                 = return $ HiValueNumber (toRational $ T.length e)
apllyMain (HiValueFunction HiFunToUpper) [HiValueString e]                = return $ HiValueString (T.toUpper e)
apllyMain (HiValueFunction HiFunToLower) [HiValueString e]                = return $ HiValueString (T.toLower e)
apllyMain (HiValueFunction HiFunReverse) [HiValueString e]                = return $ HiValueString (T.reverse e)
apllyMain (HiValueFunction HiFunTrim) [HiValueString e]                   = return $ HiValueString (T.strip e)
apllyMain (HiValueFunction HiFunAdd) [HiValueString e1, HiValueString e2] = return $ HiValueString (e1 <> e2)
apllyMain (HiValueFunction HiFunMul) [HiValueString e, HiValueNumber cnt] = do 
                                                    when (checkIsInteger cnt) (throwE HiErrorInvalidArgument)
                                                    let repeatCnt = rationalToInt cnt
                                                    when (repeatCnt < 0) (throwE HiErrorInvalidArgument)
                                                    return $ HiValueString (stimes repeatCnt e)
apllyMain (HiValueFunction HiFunDiv) [HiValueString e1, HiValueString e2] = return $ HiValueString (e1 <> T.pack "/" <> e2)
apllyMain (HiValueString str) [HiValueNumber ind]                         = do 
                                                    when (checkIsInteger ind) (throwE HiErrorInvalidArgument)
                                                    let index = rationalToInt ind
                                                    if index < 0 then return HiValueNull else do
                                                      if index >= T.length str then return HiValueNull else do
                                                        return $ HiValueString (T.singleton (T.index str index))
apllyMain (HiValueString str) [HiValueNumber l, HiValueNumber r]          = do 
                                                    when (checkIsInteger l) (throwE HiErrorInvalidArgument)
                                                    when (checkIsInteger r) (throwE HiErrorInvalidArgument)
                                                    let from = rationalToInt l
                                                    let to = rationalToInt r
                                                    if from > T.length str || to > T.length str 
                                                      then return HiValueNull else do
                                                        return $ HiValueString (sliceText from to str)
apllyMain (HiValueString str) [HiValueNumber l, HiValueNull]              = do
                                                    when (checkIsInteger l) (throwE HiErrorInvalidArgument)
                                                    let from = rationalToInt l
                                                    let to = T.length str
                                                    return $ HiValueString (sliceText from to str)
apllyMain (HiValueString str) [HiValueNull, HiValueNumber r]              = do
                                                    when (checkIsInteger r) (throwE HiErrorInvalidArgument)
                                                    let to = rationalToInt r
                                                    let from = 0
                                                    return $ HiValueString (sliceText from to str)
apllyMain (HiValueString str) [HiValueNull, HiValueNull]                  = return $ HiValueString (sliceText 0 (T.length str) str)                                                   
apllyMain _ _                                                             = throwE HiErrorInvalidArgument

checkIsInteger :: Rational -> Bool
checkIsInteger val = denominator val /= 1

rationalToInt :: Rational -> Int
rationalToInt = fromInteger .numerator

sliceText :: Int -> Int -> T.Text -> T.Text
sliceText l r str = do
  let len = T.length str
  if len == 0  || l == r then T.empty else do
                    let from = (l + len) `mod` len
                    let to = (r + len - 1) `mod` len
                    T.take (to + 1 - from) (T.drop from str)
