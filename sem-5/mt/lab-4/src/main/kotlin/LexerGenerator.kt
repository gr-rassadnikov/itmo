class LexerGenerator(private val collector: GrammarStorage) {
    private val wr = Writer()

    fun run() : StringBuilder {
        wr.line("import Foundation\n")
        wr.line("enum Token: Int {")
        wr.scope {
            collector.allTokens.forEach {
                wr.line("case ${it.key}")
            }
        }
        wr.line("}")

        wr.line("")
        wr.line("let patterns: [Token: NSRegularExpression] = [")
        wr.scope {
            collector.allTokens.forEach {
                val enc = needBackEnc()
                wr.line(".${it.key}: try! NSRegularExpression(pattern: \"$enc${it.value}\"), ")
            }
        }
        wr.line("]")

        wr.line(
            "class Lexer {\n" +
                    "    private let skipSmbls = try! NSRegularExpression(pattern:  \"[ \\n\\r\\t]\")\n" +
                    "    private var current = 0\n" +
                    "    private let input: String\n" +
                    "    \n" +
                    "    \n" +
                    "    init(input: String) {\n" +
                    "        self.input = input\n" +
                    "    }\n" +
                    "    \n" +
                    "    var token = Token.EOF\n" +
                    "    \n" +
                    "    func nextToken() throws -> Token {\n" +
                    "        if current >= input.count {\n" +
                    "            return Token.EOF\n" +
                    "        }\n" +
                    "        \n" +
                    "        let range = NSRange(location: current, length: input.count - current)\n" +
                    "        \n" +
                    "        guard let match = patterns\n" +
                    "            .compactMap({ \$0.value.firstMatch(in: input, range: range) })\n" +
                    "            .first(where: { \$0.range.location == current }) else {\n" +
                    "            return Token.EOF\n" +
                    "        }\n" +
                    "        \n" +
                    "        current = match.range.upperBound\n" +
                    "        token = Token(rawValue: match.range.lowerBound)!\n" +
                    "        return token\n" +
                    "    }\n" +
                    "}"
        )

        return wr.result
    }

    private fun needBackEnc(): String = ""
}