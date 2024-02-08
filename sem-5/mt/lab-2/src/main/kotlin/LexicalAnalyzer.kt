import java.text.ParseException

class LexicalAnalyzer(private val str: String) {
    var curPos = -1
    private var curChar = 0.toChar()
    var curToken: Token? = null

    init {
        nextChar()
    }

    private fun isBlank(c: Char): Boolean {
        return c == ' ' || c == '\r' || c == '\n' || c == '\t'
    }

    private fun nextChar() {
        curPos++
        curChar = if (curPos < str.length) {
            str[curPos]
        } else {
            '$'
        }
    }

    fun nextToken() {
        while (isBlank(curChar)) nextChar()

        when (curChar) {
            ';' -> {
                nextChar()
                curToken = Token.SEPARATOR
            }

            '(' -> {
                nextChar()
                curToken = Token.LPAREN
            }

            ')' -> {
                nextChar()
                curToken = Token.RPAREN
            }

            '+' -> {
                nextChar()
                curToken = if (curChar == '+') {
                    nextChar()
                    Token.INC
                } else {
                    throw ParseException("ERROR: after '+' expected '+', but found '$curChar'.", curPos)
                }
            }

            '-' -> {
                nextChar()
                curToken = if (curChar == '-') {
                    nextChar()
                    Token.DEC
                } else if (curChar.isDigit()) {
                    parseNumber()
                    Token.NUMBER
                } else {
                    throw ParseException("ERROR: after '-' expected '-' or digit, but found '$curChar'.", curPos)
                }
            }


            '!' -> {
                nextChar()
                if (curChar == '=') {
                    curToken = Token.NEQ
                    nextChar()
                } else {
                    throw ParseException("ERROR: after '!' expected '=', but found '$curChar'.", curPos)
                }
            }

            '=' -> {
                nextChar()
                if (curChar == '=') {
                    curToken = Token.EQ
                    nextChar()
                } else {
                    curToken = Token.ASSIGN
                }
            }

            '<' -> {
                nextChar()
                if (curChar == '=') {
                    curToken = Token.LE
                    nextChar()
                } else {
                    curToken = Token.LT
                }
            }

            '>' -> {
                nextChar()
                if (curChar == '=') {
                    curToken = Token.GE
                    nextChar()
                } else {
                    curToken = Token.GT
                }
            }

            ',' -> {
                nextChar()
                curToken = Token.COMMA
            }


            '$' -> {
                curToken = Token.END
            }

            else -> {
                curToken = parseHardToken()
            }
        }
    }

    private fun parseHardToken(): Token {
        if (curChar.isDigit()) {
            parseNumber()
            return Token.NUMBER
        } else if (curChar.isCTypeLetter()) {
            val result = parseWord()
            if (result == "for") return Token.FOR
            return Token.VAR
        } else {
            throw ParseException("ERROR: expected letter or digit, but found '$curChar'.", curPos)
        }
    }

    private fun parseWord(): String {
        val sb = StringBuilder()
        while (curChar.isCTypeLetter()) {
            sb.append(curChar)
            nextChar()
        }
        val result = sb.toString()
        if (result.checkIsCTypeLetter()) {
            return result
        } else {
            throw ParseException("ERROR: can't cast value to 'C-type name'.", curPos)
        }
    }

    private fun parseNumber(): String {
        val sb = StringBuilder()
        while (curChar.isCTypeDigit()) {
            sb.append(curChar)
            nextChar()
        }
        val result = sb.toString()
        if (sb.toString().checkIsCTypeNumber()) {
            return result
        } else {
            throw ParseException("ERROR: can't cast value to 'C-type number'.", curPos)
        }
    }
}

private fun Char.isCTypeLetter() = this.isLetter() || this.isDigit() || this == '_'
private fun Char.isCTypeDigit() = this.isLetter() || this.isDigit() || this == '.'

private fun String.checkIsCTypeLetter(): Boolean {
    return !this.first().isDigit()
}

private fun String.checkIsCTypeNumber(): Boolean =
    this.matches(Regex("-?[0-9]+"))
            || this.matches(Regex("-?[0-9]+.[0-9]+"))
            || this.matches(Regex("-?[0-9]+e[0-9]+"))
            || this.matches(Regex("-?0x[0-9]+"))
            || this.matches(Regex("-?[0-9]+l"))

