module HW5.Parser (parse) where

import HW5.Base
import Data.Void (Void)
import qualified Data.Text as T
import qualified Text.Megaparsec.Char.Lexer as L
import Text.Megaparsec.Char (string, space, space1, char)
import Text.Megaparsec (MonadParsec (eof), ParseErrorBundle, Parsec, runParser, try, choice, empty, sepBy, notFollowedBy, manyTill, (<|>))
import Control.Monad.Combinators.Expr (makeExprParser, Operator (InfixL, InfixR, InfixN))

type Parser = Parsec Void String

parse :: String -> Either (ParseErrorBundle String Void) HiExpr
parse = runParser (space *> parseExpr <* eof) ""

parseExpr :: Parser HiExpr
parseExpr = makeExprParser parseTerm operators

sc :: Parser ()
sc = L.space space1 empty empty

lexeme :: Parser a -> Parser a
lexeme = L.lexeme sc

symbol :: String -> Parser String
symbol = L.symbol sc

parseValueNumber :: Parser HiValue
parseValueNumber = lexeme $ HiValueNumber . toRational <$> L.signed space L.scientific

parseValueFunction :: Parser HiValue
parseValueFunction = lexeme $ HiValueFunction <$> choice
  [ HiFunDiv            <$ string "div"
  , HiFunMul            <$ string "mul"
  , HiFunAdd            <$ string "add"
  , HiFunSub            <$ string "sub"
  , HiFunAnd            <$ string "and"
  , HiFunOr             <$ string "or"
  , HiFunNotLessThan    <$ string "not-less-than"
  , HiFunNotGreaterThan <$ string "not-greater-than"
  , HiFunNotEquals      <$ string "not-equals"
  , HiFunLessThan       <$ string "less-than"
  , HiFunGreaterThan    <$ string "greater-than"
  , HiFunEquals         <$ string "equals"
  , HiFunIf             <$ string "if"
  , HiFunNot            <$ string "not"
  , HiFunLength         <$ string "length"
  , HiFunToUpper        <$ string  "to-upper"
  , HiFunToLower        <$ string  "to-lower"
  , HiFunReverse        <$ string  "reverse"
  , HiFunTrim           <$ string  "trim"
  ]

parseValueBool :: Parser HiValue
parseValueBool = lexeme $ choice
  [ HiValueBool False <$ string "false",
    HiValueBool True  <$ string "true"
  ]

parseValueString :: Parser HiValue
parseValueString = lexeme $ choice
  [ HiValueString . T.pack <$> (char '\"' *> manyTill L.charLiteral (char '\"')), 
    HiValueNull <$ string "null"
  ]

parseValueBr :: Parser HiExpr
parseValueBr = choice [
   HiExprValue <$> choice [
    parseValueFunction,
    parseValueNumber,
    parseValueBool,
    parseValueString
   ]
  , symbol "(" *> parseExpr <* symbol ")"
  ]

parseInBracket :: String -> Parser [a] -> String -> Parser [a]
parseInBracket opentBr str closeBr = do
  _ <- lexeme $ symbol opentBr
  args <- str
  _ <- lexeme $ symbol closeBr
  return args

parseTerm :: Parser HiExpr
parseTerm = parseTermReduce =<< parseValueBr

parseTermReduce :: HiExpr -> Parser HiExpr
parseTermReduce expr = try (parseTermReduce =<<
                        HiExprApply expr <$> parseInBracket "(" (parseExpr `sepBy` symbol ",") ")"
                      ) <|> pure expr

operators :: [[Operator Parser HiExpr]]
operators = [
   [ InfixL (hiFunApp HiFunMul <$ symbol "*"),
     InfixL (hiFunApp HiFunDiv <$ try (symbol "/" <* notFollowedBy (string "=")))
    ],
    [ InfixL (hiFunApp HiFunAdd <$ symbol "+"),
      InfixL (hiFunApp HiFunSub <$ symbol "-")
    ],
    [ InfixN (hiFunApp HiFunEquals <$ symbol "=="),
      InfixN (hiFunApp HiFunNotEquals <$ symbol "/="),
      InfixN (hiFunApp HiFunNotGreaterThan <$ symbol "<="),
      InfixN (hiFunApp HiFunNotLessThan <$ symbol ">="),
      InfixN (hiFunApp HiFunLessThan <$ symbol "<"),
      InfixN (hiFunApp HiFunGreaterThan <$ symbol ">")
    ],
    [InfixR (hiFunApp HiFunAnd <$ symbol "&&")],
    [InfixR (hiFunApp HiFunOr <$ symbol "||")]
  ]

hiFunApp :: HiFun -> HiExpr -> HiExpr -> HiExpr
hiFunApp hiFun l r = HiExprApply (HiExprValue $ HiValueFunction hiFun) [l, r]
