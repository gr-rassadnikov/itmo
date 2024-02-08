import org.junit.jupiter.api.Test
import org.junit.jupiter.api.assertDoesNotThrow
import org.junit.jupiter.api.assertThrows
import java.text.ParseException

class ParserTest {

    @Test

    fun test() {
        assertDoesNotThrow { runParser("  for  ( long x = -1; x <= 100 ;  x++  )") }
        assertDoesNotThrow { runParser("for (__int64 _y1 = -2323; x != -234; x--)") }
        assertDoesNotThrow { runParser("for \n\n(int \rx = 0; x \t< 10; x++)\n\n") }

        assertDoesNotThrow { runParser("for (int x12 = 1l ; x < 10; x++)") }


        assertThrows<ParseException> { runParser("for (int x = 0; x < 10; x++) {\n}") }
        assertThrows<ParseException> { runParser("for (int x = 0; x < 10; ++x)") }
        assertThrows<ParseException> { runParser("for (int x = 0; x < 10; --x++)") }
    }

    @Test
    fun testCStyle() {
        assertThrows<ParseException> { runParser("for (int 1x = 0; x < 10; x++)") }
        assertThrows<ParseException> { runParser("for (1int x = 0; x < 10; x++)") }
        assertThrows<ParseException> { runParser("for (int x[y] = 0; x < 10; x++)") }

        assertDoesNotThrow { runParser("for (int x = 1.5; x < 10; x++)") }
        assertDoesNotThrow { runParser("for (int x = 2e4; x < 10; x++)") }
        assertDoesNotThrow { runParser("for (int x = -1l; x < 10; x++)") }
        assertDoesNotThrow { runParser("for (int x = 0x12; x < 10; x++)") }
        assertDoesNotThrow { runParser("for (int x12 = 1l ; x < 10; x++)")}
    }

    @Test
    fun testWithVarArg() {
        assertDoesNotThrow { runParser("for (int x = 0, y = 1 ; x < 10; x++)") }
        assertDoesNotThrow { runParser("for (int x = 0, y = 1, z=-1 ; x < 10; x++)") }
        assertThrows<ParseException> { runParser("for (int x = 0, int y = 0; x < 10; x++)") }
        assertThrows<ParseException> { runParser("for (int x = 0; y = 0; x < 10; x++)") }
    }


    @Throws(ParseException::class)
    private fun runParser(with: String): Node {
        val parser = Parser(with)
        return parser.parse()
    }
}
