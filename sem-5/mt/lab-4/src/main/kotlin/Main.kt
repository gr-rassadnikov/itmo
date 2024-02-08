import antlr.GrammarLexer
import org.antlr.v4.runtime.CharStreams
import org.antlr.v4.runtime.CommonTokenStream
import antlr.GrammarParser
import org.antlr.v4.runtime.tree.ParseTreeWalker
import java.nio.file.Files
import java.nio.file.Paths

fun main() {
    val input = "mathCalculator.gram"
    val directory = "swift"

    val storage = GrammarStorage()
    val grammarLexer = GrammarLexer(CharStreams.fromFileName(input))
    val grammarParser = GrammarParser(CommonTokenStream(grammarLexer))
    val walker = ParseTreeWalker()
    walker.walk(storage, grammarParser.file())

    storage.checkLL1()
    val lexer = LexerGenerator(storage)

    val outLexer = Paths.get(directory, "Lexer.kt")
    Files.newBufferedWriter(outLexer).use { wr ->
        wr.write(lexer.run().toString())
    }

    val parser = ParserGenerator(storage)

    val outParser = Paths.get(directory, "Parser.kt")
    Files.newBufferedWriter(outParser).use { wr ->
        wr.write(parser.run().toString())
    }
}