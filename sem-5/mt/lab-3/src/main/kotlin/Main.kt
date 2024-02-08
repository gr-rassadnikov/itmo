import org.antlr.v4.runtime.CharStreams
import org.antlr.v4.runtime.CommonTokenStream
import java.io.FileInputStream
import java.io.FileNotFoundException
import kotlin.math.log


fun main(args: Array<String>) {
    val inputStream: FileInputStream? = if (args.isNotEmpty()) {
        try {
            FileInputStream(args[0])
        } catch (e: FileNotFoundException) {
            println("ERROR: can't found file ${args[0]}.${e.message}")
            null
        }
    } else {
        println("ERROR: expected input-file at first arguments.")
        null
    }
    if (inputStream != null) {
        val charStream = CharStreams.fromStream(inputStream)
        val lexer = MathExprLexer(charStream)
        val tokens = CommonTokenStream(lexer)
        val parser = MathExprParser(tokens)
        val logMathExprResult = LogMathExprResult()
        val visitor = MathExprCalculateVisitor(logMathExprResult)

        visitor.visit(parser.let())
    }

}
