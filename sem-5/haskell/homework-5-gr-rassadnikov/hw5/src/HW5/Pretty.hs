{-# LANGUAGE TypeApplications  #-}

module HW5.Pretty(prettyValue, prettyParseError, prettyEvalError) where

import HW5.Base
import Data.Void (Void)
import Data.Ratio
import Data.Scientific
import Numeric (showFFloat)
import Prettyprinter (Doc, pretty, annotate, viaShow, (<+>))
import Prettyprinter.Render.Terminal
import Text.Megaparsec (ParseErrorBundle, errorBundlePretty)

prettyEvalError :: HiError -> Doc AnsiStyle
prettyEvalError err = annotate (color Red) (pretty (show err))

prettyParseError :: ParseErrorBundle String Void -> Doc AnsiStyle
prettyParseError = annotate (color Red) . pretty . errorBundlePretty

prettyValue :: HiValue -> Doc AnsiStyle
prettyValue (HiValueNumber val) = prettyRational val
prettyValue (HiValueFunction fun) = prettyFun fun
prettyValue (HiValueBool val) = prettyValueBool val
prettyValue (HiValueString str) = viaShow str
prettyValue HiValueNull = pretty @String "null"

prettyFun :: HiFun -> Doc AnsiStyle
prettyFun HiFunAdd            = pretty @String "add"
prettyFun HiFunSub            = pretty @String "sub"
prettyFun HiFunDiv            = pretty @String "div"
prettyFun HiFunMul            = pretty @String "mul"
prettyFun HiFunNot            = pretty @String "not"
prettyFun HiFunAnd            = pretty @String "and"
prettyFun HiFunOr             = pretty @String "or"
prettyFun HiFunNotLessThan    = pretty @String "not-less-than"
prettyFun HiFunNotGreaterThan = pretty @String "not-greater-than"
prettyFun HiFunNotEquals      = pretty @String "not-equals"
prettyFun HiFunLessThan       = pretty @String "less-than"
prettyFun HiFunGreaterThan    = pretty @String "greater-than"
prettyFun HiFunEquals         = pretty @String "equals"
prettyFun HiFunIf             = pretty @String "if"
prettyFun HiFunLength         = pretty @String "length"
prettyFun HiFunToUpper        = pretty @String "to-upper"
prettyFun HiFunToLower        = pretty @String "to-lower"
prettyFun HiFunReverse        = pretty @String "reverse"
prettyFun HiFunTrim           = pretty @String "trim"

prettyRational :: Rational -> Doc AnsiStyle
prettyRational value = case denominator value of 
                          1 -> pretty (numerator value)
                          d -> prettyDecimalFraction value (numerator value) d

prettyDecimalFraction :: Rational -> Integer -> Integer -> Doc AnsiStyle
prettyDecimalFraction value n d = 
                          if checkIsDecimalFormat d then
                                    pretty @String
                                      (showFFloat @Double Nothing (toRealFloat (fst (fromRationalRepetendUnlimited value))) "")
                          else prettyRightFraction (quotRem n d) d

prettyRightFraction :: (Integer, Integer) -> Integer -> Doc AnsiStyle
prettyRightFraction (0, n) d   = pretty n <> pretty @String "/" <> pretty d
prettyRightFraction (val, n) d = pretty val <+> prettySignOfFraction n <+> prettyRightFraction (0, abs n) d

prettySignOfFraction :: Integer -> Doc AnsiStyle
prettySignOfFraction n = if n > 0 then pretty @String "+" else pretty @String "-"

prettyValueBool :: Bool -> Doc AnsiStyle
prettyValueBool False = pretty "false"
prettyValueBool True = pretty "true"

checkIsDecimalFormat :: Integer -> Bool
checkIsDecimalFormat d = divOnAllDegree (divOnAllDegree d 5) 2 == 1

divOnAllDegree :: Integer -> Integer -> Integer
divOnAllDegree n d = if mod n d == 0 then divOnAllDegree (div n d) d else n
