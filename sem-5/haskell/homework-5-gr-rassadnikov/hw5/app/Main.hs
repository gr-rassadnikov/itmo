module Main(main) where

import HW5.Evaluator (eval)
import HW5.Parser (parse)
import HW5.Pretty (prettyEvalError, prettyParseError, prettyValue)
import Control.Monad.IO.Class (MonadIO (liftIO))
import System.Console.Haskeline (InputT, defaultSettings, getInputLine, runInputT)
import Prettyprinter.Render.Terminal (putDoc)

main :: IO ()
main = runInputT defaultSettings loop
   where
       loop :: InputT IO ()
       loop = do
           minput <- getInputLine "hi> "
           case minput of
               Nothing -> return ()
               Just "quit" -> return ()
               Just input -> do 
                let parsed = parse input
                liftIO $ case parsed of
                    Left err -> putDoc . prettyParseError $ err
                    Right expr -> do
                        result <-  eval expr
                        putDoc (case result of
                            Left err  -> prettyEvalError err
                            Right value -> prettyValue value) <> putStrLn ""
                loop
