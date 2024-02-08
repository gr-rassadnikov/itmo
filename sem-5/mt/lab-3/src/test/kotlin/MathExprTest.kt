import org.antlr.v4.runtime.CharStreams
import org.antlr.v4.runtime.CommonTokenStream
import org.junit.Assert
import org.junit.jupiter.api.Assertions
import org.junit.jupiter.api.Test
import org.opentest4j.AssertionFailedError
import java.io.ByteArrayInputStream
import java.io.InputStream
import java.text.ParseException
import kotlin.math.log


class MathExprTest {

    @Test
    fun simpleTest() {

        Assertions.assertEquals(
            "a = 2\n" +
                    "b = 4\n" +
                    "c = 6\n" +
                    "a = 3\n" +
                    "c = 7\n",
            evalMathExp(
                "a = 2;\n" +
                        "b = a + 2;\n" +
                        "c = a + b * (b - 3);\n" +
                        "a = 3;\n" +
                        "c = a + b * (b - 3);\n"
            )
        )

        Assertions.assertEquals(
            "a = -7\n",
            evalMathExp("a = 1 + 2 * 3 / 4 - 9;\n")
        )

    }

    @Test
    fun smartMathTest() {
        Assertions.assertEquals(
            "x = 1329308\n",
            evalMathExp("x = (1) + (2231) + (-2 + 3 * 2 - 1) * (12 - 122)*(23 - 122 * 32)+(((321) + 213*213) + 3212 - (213 * 12));\n")
        )

        Assertions.assertEquals(
            "x = 5\n",
            evalMathExp("x = 10 / 3 / 2 + 7 * 2 - (10 / 2 * 3) + 5;\n")
        )
    }

    @Test
    fun bigInteger() {
        Assertions.assertThrows(
            ParseException::class.java
        ) {
            evalMathExp("x = 929131291238991231728317237213 - 929131291238991231728317237213 * 1 + 1 * 1;")
        }
    }

    @Test
    fun errorsTest() {
        Assertions.assertThrows(ParseException::class.java) { evalMathExp("x = y;\n") }
        Assertions.assertDoesNotThrow { evalMathExp("x == 1;\n") }
        Assertions.assertDoesNotThrow { evalMathExp("(x = 1 + 1);\n") }
        Assertions.assertDoesNotThrow { evalMathExp("x = 1);\n") }
        Assertions.assertDoesNotThrow { evalMathExp("x = @1;\n") }
        Assertions.assertThrows(ParseException::class.java) { evalMathExp("x = - - - 1;\n") }
        Assertions.assertDoesNotThrow { evalMathExp("x = +1;\n") }
        Assertions.assertThrows(ParseException::class.java) { evalMathExp("x = 1 - 3 /\n;") }
    }

    @Test
    fun separatorTest() {
        Assertions.assertDoesNotThrow {
            evalMathExp(
                "x = \t\t\r 1 \r \t - 2\n +4\n ;\t"
            )
        }

        Assertions.assertDoesNotThrow {
            evalMathExp(
                "\n x =\t       2;" +
                        "y       =     x\n\n\n;" +
                        "\nz=\t  x     +     y;\n"
            )
        }
    }

    @Test
    fun binomialTest() {
        Assertions.assertEquals(
            "x = 10\n",
            evalMathExp("x = C(5, 3);\n")
        )

        Assertions.assertEquals(
            "x = 10\n",
            evalMathExp("x = C(1 + 2 * 3 - 2, 15 / 5 + 1 - 1);\n")
        )

        Assertions.assertEquals(
            "y = 5\n" +
                    "z = 3\n" +
                    "x = 10\n",
            evalMathExp(
                "y = 4 + 1;\n" +
                        "z = 2 + 1;\n" +
                        "x = C(y, z);\n"
            )
        )

        Assertions.assertThrows(ParseException::class.java) { evalMathExp("x = C(-1, 0);\n") }

        Assertions.assertEquals(
            "x = 100\n",
            evalMathExp("x = C(100, 1);\n")
        )

        Assertions.assertThrows(ParseException::class.java) { evalMathExp("x = C(100, 23);\n") }

        Assertions.assertEquals(
            "x = 10\n",
            evalMathExp("\nx \t=\t\t\t \r\rC\n(\n5, \n3\n);\n\n")
        )
    }


    @Throws(ParseException::class)
    private fun evalMathExp(str: String): String {
        val inputStream: InputStream = str.byteInputStream()
        val chartStream = CharStreams.fromStream(inputStream)
        val lexer = MathExprLexer(chartStream)
        val tokens = CommonTokenStream(lexer)
        val parser = MathExprParser(tokens)
        val logMathExprResult = LogMathExprResult()
        val visitor = MathExprCalculateVisitor(logMathExprResult)
        visitor.visit(parser.let())

        return logMathExprResult.result()
    }

}