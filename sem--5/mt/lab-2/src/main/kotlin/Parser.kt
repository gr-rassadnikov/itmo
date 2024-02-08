import java.text.ParseException

class Parser(str: String) {
    private val x = LexicalAnalyzer(str)

    fun parse(): Node {
        x.nextToken()
        return S()
    }

    private fun S(): Node {
        checkToken(Token.FOR)

        goToNextToken(Token.LPAREN)

        goToNextToken(Token.VAR)
        goToNextToken(Token.VAR)
        goToNextToken(Token.ASSIGN)
        goToNextToken(Token.NUMBER)
        goToNext()

        val varArg = VARARG()

        checkToken(Token.SEPARATOR)

        goToNextToken(Token.VAR)

        val op = OP()
        goToNextToken(Token.NUMBER)
        goToNextToken(Token.SEPARATOR)
        goToNextToken(Token.VAR)

        val nc = NC()

        goToNextToken(Token.RPAREN)
        goToNextToken(Token.END)

        return Node(
            "S",
            Node("for"),
            Node("("),
            Node("type"),
            Node("variable"),
            Node("="),
            Node("number", varArg),
            Node(";"),
            Node("variable"),
            op,
            Node("number"),
            Node(";"),
            Node("variable"),
            nc,
            Node(")"),
        )
    }

    private fun VARARG(): List<Node> {
        if (!getNextToken(Token.COMMA)) return emptyList()
        goToNextToken(Token.VAR)
        goToNextToken(Token.ASSIGN)
        goToNextToken(Token.NUMBER)

        x.nextToken()
        val varArg = VARARG()
        return listOf(Node(","), Node("variable"), Node("="), Node("number", varArg))
    }

    private fun OP(): Node {
        x.nextToken()
        return when (x.curToken) {
            Token.LT -> {
                Node("OP", Node("<"))
            }

            Token.LE -> {
                Node("OP", Node("<="))
            }

            Token.GT -> {
                Node("OP", Node(">"))
            }

            Token.GE -> {
                Node("OP", Node(">="))
            }

            Token.EQ -> {
                Node("OP", Node("=="))
            }

            Token.NEQ -> {
                Node("OP", Node("!="))
            }

            else -> {
                throw ParseException(
                    "ERROR: expected '>'/'>='/'<'/'<='/'=='/''!= , but found '${x.curToken}'.",
                    x.curPos
                )
            }
        }
    }

    private fun NC(): Node {
        x.nextToken()
        return when (x.curToken) {
            Token.INC -> {
                Node("NC", Node("++"))
            }

            Token.DEC -> {
                Node("NC", Node("--"))
            }

            else -> {
                throw ParseException("ERROR: expected '++'/'--', but found '${x.curToken}'.", x.curPos)
            }
        }
    }

    private fun goToNext() {
        x.nextToken()
    }

    private fun goToNextToken(token: Token) {
        x.nextToken()
        checkToken(token)
    }

    private fun checkToken(token: Token) {
        if (x.curToken != token) {
            throw ParseException("ERROR: expected '$token', but found '${x.curToken}'.", x.curPos)
        }
    }

    private fun getNextToken(token: Token) = x.curToken == token
}
