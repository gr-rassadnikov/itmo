fun main() {
    val (k1, k2) = readln().split(" ").map { it.toInt() }
    val n = readln().toInt()

    val countX = LongArray(k1)
    val countY = LongArray(k2)

    val mp = (0..<n).map {
        val (x, y) = readln().split(" ").map { it.toInt() - 1 }
        countX[x]++
        countY[y]++
        x to y
    }

    val forum = mp.groupBy { it.first }
        .mapValues { entry ->
            entry.value
                .groupBy { it.second }
                .mapValues { it.value.size }
        }

    val xDiv = countX.map { it.toDouble() / n }
    val yDiv = countY.map { it.toDouble() / n }

    val ans = forum.flatMap { (x, y) ->
        y.map { (k, v) ->
            val a = xDiv[x] * yDiv[k] * n
            val b = v.toDouble() - a
            (b * b / a) - a
        }
    }.sum()

    println(ans + n)
}