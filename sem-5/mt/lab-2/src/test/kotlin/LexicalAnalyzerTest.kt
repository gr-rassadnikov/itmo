import org.junit.jupiter.api.Assertions.assertEquals
import org.junit.jupiter.api.Test
import org.junit.jupiter.api.assertThrows
import java.text.ParseException

class LexicalAnalyzerTest {
    @Test
    @Throws(ParseException::class)
    fun test() {
        tokensExpected(
            "for (int x = 0; x < 100; x++)",
            listOf(
                Token.FOR, Token.LPAREN,
                Token.VAR, Token.VAR,
                Token.ASSIGN, Token.NUMBER,
                Token.SEPARATOR, Token.VAR,
                Token.LT, Token.NUMBER,
                Token.SEPARATOR, Token.VAR,
                Token.INC, Token.RPAREN, Token.END
            )
        )

        tokensExpected(
            "for (__int64 x21 = 45; x21 >= -100; x21--)",
            listOf(
                Token.FOR, Token.LPAREN,
                Token.VAR, Token.VAR,
                Token.ASSIGN, Token.NUMBER,
                Token.SEPARATOR, Token.VAR,
                Token.GE, Token.NUMBER,
                Token.SEPARATOR, Token.VAR,
                Token.DEC, Token.RPAREN, Token.END
            )
        )

        tokensExpected("", listOf(Token.END))

        tokensExpected(
            "++ -- ;     -12 )() for    _what_ = == <=",
            listOf(
                Token.INC, Token.DEC,
                Token.SEPARATOR, Token.NUMBER,
                Token.RPAREN, Token.LPAREN,
                Token.RPAREN, Token.FOR,
                Token.VAR, Token.ASSIGN,
                Token.EQ, Token.LE, Token.END
            )
        )

        errorExpected("+-")
        errorExpected("!<")

        errorExpected("for (int x = 0; x < 100; x++) {}")
    }


    private fun tokensExpected(with: String, expected: List<Token?>) {
        val lexicalAnalyzer = LexicalAnalyzer(with)
        val tokens = mutableListOf<Token?>()
        var curToken = lexicalAnalyzer.curToken
        while (curToken != Token.END) {
            lexicalAnalyzer.nextToken()
            curToken = lexicalAnalyzer.curToken
            tokens.add(curToken)
        }
        assertEquals(expected, tokens)
    }

    private fun errorExpected(with: String) {
        assertThrows<ParseException> {
            val lexicalAnalyzer = LexicalAnalyzer(with)
            val tokens = mutableListOf<Token?>()
            var curToken = lexicalAnalyzer.curToken
            while (curToken != Token.END) {
                lexicalAnalyzer.nextToken()
                curToken = lexicalAnalyzer.curToken
                tokens.add(curToken)
            }
        }
    }

}
