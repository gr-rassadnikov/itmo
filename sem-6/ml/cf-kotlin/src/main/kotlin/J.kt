import kotlin.math.abs

fun main() {

    val k = readln().toInt()
    val n = readln().toInt()

    val a = List(n) {
        val (x, y) = readln().split(" ").map { it.toInt() }
        Pair(x, y)
    }

    val diff: Double = a.sumOf { it.second.toDouble() / n.toDouble() * it.second.toDouble() }

    val X = mutableMapOf<Int, Double>()
    val Y = mutableMapOf<Int, Double>()

    a.forEach { (x, y) ->
        X[x - 1] = X.getOrDefault(x - 1, 0.0) + 1.0 / n.toDouble()
        Y[x - 1] = Y.getOrDefault(x - 1, 0.0) + y.toDouble() / n.toDouble()
    }

    val mp = (X.toList() + Y.toList())
    val d = mp.groupBy({ it.first }, { it.second }).mapValues { (_, v) -> Pair(v[0], v[1]) }

    val e = d.values.filter { (x, _) -> abs(x) > 1e-7 }.sumOf { (x, y) -> y * y / x }
    println(diff - e)
}