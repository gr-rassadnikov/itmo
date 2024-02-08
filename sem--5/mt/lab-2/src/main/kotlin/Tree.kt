import java.lang.StringBuilder
import java.util.*


class Node(
    private val value: String,
    private val children: List<Node> = listOf()
) {
    constructor(node: String, vararg children: Node) : this(node, children.asList())

    fun toGraph(ind: Int, sb: StringBuilder): Pair<Int, Int> {
        var n = ind
        sb.append(String.format("%d [label = \"%s\"]\n", ind, value))
        for (to in children) {
            val p = to.toGraph(n + 1, sb)
            n = p.second
            sb.append(String.format("%d -> %d\n", ind, p.first))
        }
        return ind to n
    }

}
