import antlr.GrammarBaseListener
import antlr.GrammarParser
import java.text.ParseException

class GrammarStorage : GrammarBaseListener() {
    companion object {
        const val EPS = "EPS"
        const val EOF = "EOF"
    }

    private var counter = 0

    val allTokens: MutableMap<String, Int> = LinkedHashMap()

    private val tokenString: MutableMap<Int, Regex> = HashMap()
    private val tokenRegex: MutableMap<Int, String> = HashMap()

    val allRules: MutableMap<String, Rule> = LinkedHashMap()

    var start: String = "<start>"

    init {
        allTokens[EOF] = -1

    }

    fun terms(): Set<String> = allTokens.keys

    fun nonTerms(): Set<String> = allRules.keys

    override fun exitStart(ctx: GrammarParser.StartContext) {
        start = ctx.NONTERM().text
    }

    override fun exitRParse(ctx: GrammarParser.RParseContext) {
        super.exitRParse(ctx)
        val curRule = allRules.getOrPut(ctx.NONTERM().text, { Rule(ctx.NONTERM().text) })

        if (ctx.synthesized() != null)
            curRule.returnType = ctx.synthesized().text
        if (ctx.inherited() != null)
            curRule.arguments = ctx.inherited().param().map { Argument(it.TERM().text, it.NONTERM().text) }

    }

    override fun exitTokenLex(ctx: GrammarParser.TokenLexContext) {
        val token = allTokens.getOrPut(ctx.TERM().text) { counter++ }
        if (ctx.term_value().STRING() != null) {
            tokenRegex[token] = ctx.term_value().STRING().text.trim('\"')
        } else {
            tokenString[token] = Regex(ctx.term_value().REG().text.trim('\''))
        }
    }

    fun checkLL1() {
        for ((name, rule) in allRules) {
            if (rule.productions.any { production -> production.nodes.first().name == name }) {
                throw ParseException("ERROR: you grammar is not LL1!", -1)
            }
        }

        for (rule in allRules.values) {
            if (rule.productions.any { fst ->
                    rule.productions.any { scnd ->
                        fst != scnd && fst.nodes.first().name == scnd.nodes.first().name
                    }
                }) {
                throw ParseException("ERROR: you grammar is not LL1!", -1)
            }
        }
    }

    fun first(): Map<String, Set<String>> {
        val fst: MutableMap<String, MutableSet<String>> = mutableMapOf()

        terms().forEach { fst[it] = mutableSetOf(it) }
        allRules.forEach { (name, rule) ->
            fst[name] = mutableSetOf()
            if (rule.productions.any { it.nodes.first().name == EPS }) fst[name]?.add(
                EPS
            )
        }

        var change = true
        while (change) {
            change = false
            for (rule in allRules) {
                for (prod in rule.value.productions) {
                    for (i in prod.nodes.indices) {
                        val nonTerm = prod.nodes[i].name
                        if (EPS in fst.getValue(nonTerm)) {
                            change = change || fst.getValue(rule.key).addAll(fst.getValue(nonTerm))
                            if (i == prod.nodes.size - 1) {
                                change = change || fst.getValue(rule.key).add(EPS)
                            }
                        } else {
                            change = change || fst.getValue(rule.key).addAll(fst.getValue(nonTerm))
                            break
                        }
                    }
                }
            }
        }
        return fst
    }

    fun follow(): Map<String, Set<String>> {
        val flw: MutableMap<String, MutableSet<String>> = mutableMapOf()
        val fst = first()

        nonTerms().forEach { flw[it] = mutableSetOf() }
        flw.getValue(start).add(EOF)

        var change = true
        while (change) {
            change = false
            for (rule in allRules) {
                rule.value.productions.forEach { prod ->
                    for (i in 0..prod.nodes.size - 2) {
                        if (prod.nodes[i] is State.NonTerm) {
                            change = change || flw.getValue(prod.nodes[i].name).addAll(
                                fst.getValue(prod.nodes[i + 1].name).filter { it != EPS }
                            )
                        }
                    }
                    if (prod.nodes.last() is State.NonTerm)
                        change = change || flw.getValue(prod.nodes.last().name).addAll(flw.getValue(rule.key))
                    if (prod.nodes.size > 1 && EPS in fst.getValue(prod.nodes.last().name)) {
                        val afterFlw = prod.nodes[prod.nodes.size - 2]
                        if (afterFlw is State.NonTerm)
                            change = change || flw.getValue(afterFlw.name).addAll(flw.getValue(rule.key))
                    }
                }
            }
        }
        return flw
    }
}
