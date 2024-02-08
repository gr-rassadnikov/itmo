class ParserGenerator(private val storage: GrammarStorage) {
    companion object {
        const val EPS = "EPS"
        const val EOF = "EOF"
    }

    private val wr = Writer()

    fun run(): StringBuilder {
        wr.line(
            "import Foundation\n" +
                    "\n" +
                    "enum GrammarException : Error {\n" +
                    "    case Parse(mes: String = \"\", pos: Int = -1)\n" +
                    "}\n" +
                    "\n" +
                    "class Parser {"
        )
        wr.scope {
            wr.line(
                "let lexer: Lexer\n" +
                        "\n" +
                        "    init(lexer: Lexer) {\n" +
                        "        self.lexer = lexer\n" +
                        "    }\n" +
                        "\n" +
                        "    private func skip(token: Token) throws -> String {\n" +
                        "        if lexer.token != token {\n" +
                        "            throw GrammarException.Parse()\n" +
                        "        }\n" +
                        "        return try patterns[lexer.nextToken()]?.pattern ?? \"error\"\n" +
                        "    }"
            )

            wr.line(
                "func parse() throws -> Int {\n" +
                        "        try lexer.nextToken()\n" +
                        "        return try expr()\n" +
                        "    }"
            )

            for ((name, rule) in storage.allRules) {
                wr.line(
                    (
                            "private func ${name.capitalize()}(${rule.arguments?.map { "${it.name}: ${it.type}" }}) throws ${
                                rule.returnType
                                    ?: "Void"
                            } {\n"
                                    + "switch lexer.token { "
                            )
                )
                wr.scope { ->
                    for ((prod, tokens) in rule.productions
                        .associate { prod ->
                            if (prod.nodes[0].name == EPS) prod to storage.follow().getValue(name).toList()
                            else prod to storage.first().getValue(prod.nodes[0].name).toList()
                        }) {
                        wr.line("case ${tokens.joinToString { ".$it" }} :")
                        wr.scope {
                            val lst = prod.nodes.asSequence().groupingBy { it.name }.eachCount().filterValues { i -> i > 1 }
                            lst.forEach { e ->
                                when (e.key) {
                                    in storage.terms() -> wr.line("let $e : [String] = []")
                                    in storage.nonTerms() -> {
                                        val returnType = storage.allRules[e.key]!!.returnType
                                        if (returnType != null)
                                            wr.line("let $e : [$returnType] = []")
                                    }
                                }
                            }

                            for (sate in prod.attrs) {
                                when (sate) {
                                    is State.Term -> {
                                        if (sate.name == EPS) continue
                                        if (sate.name in lst)
                                            wr.line("${sate.name}.append(skip(token: .${sate.name}))")
                                        else
                                            wr.line("val ${sate.name} = skip(token: .${sate.name})")
                                    }

                                    is State.NonTerm -> {
                                        val attrs = sate.attrs?.joinToString().orEmpty()
                                        if (sate.name in lst)
                                            wr.line("${sate.name}.add(${sate.name.capitalize()}($attrs))")
                                        else
                                            wr.line("let ${sate.name} = ${sate.name.capitalize()}($attrs)")
                                    }

                                    is State.Code -> wr.line(sate.code)
                                }
                            }
                        }
                        wr.line("}")
                    }

                    wr.line("default: throw GrammarException.Parse()")
                }
                wr.line("}")

            }
            wr.line("}")
        }
        wr.line("}")
        return wr.result
    }
}
