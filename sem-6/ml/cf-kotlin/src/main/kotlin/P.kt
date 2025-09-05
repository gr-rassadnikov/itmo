import kotlin.math.ln

fun main() {
    val (_, _) = readln().split(" ").map { it.toInt() }
    val n = readln().toInt()

    val a = List(n) {
        val (x, y) = readln().split(" ").map { it.toInt() }
        Pair(x, y)
    }

    val X = mutableMapOf<Int, Int>()
    val XY = mutableMapOf<Pair<Int, Int>, Int>()

    a.forEach { (x, y) ->
        X[x] = X.getOrDefault(x, 0) + 1
        XY[Pair(x, y)] = XY.getOrDefault(Pair(x, y), 0) + 1
    }

    val XDiv = X.mapValues { it.value.toDouble() / n }
    val XYDiv = XY.mapValues { it.value.toDouble() / n }

    println(-XYDiv.entries.sumOf { (key, value) ->
        value * (ln(value) - ln(XDiv.getValue(key.first)))
    })
}