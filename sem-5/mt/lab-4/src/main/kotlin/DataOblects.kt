data class Argument(
    val name: String,
    val type: String
)


sealed interface State {
    val name: String

    data class Term(override val name: String) : State
    data class NonTerm(override val name: String, val attrs: List<String>?) : State
    data class Code(override val name: String = "code", val code: String) : State
}

data class Production(
    val nodes: List<State>,
    val attrs: List<State>
)


data class Rule(
    val name: String,
    var productions: List<Production> = emptyList(),
    var arguments: List<Argument>? = null,
    var returnType: String? = null
)