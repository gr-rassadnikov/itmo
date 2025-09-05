import java.util.*

fun formula(sum: Long, n: Long): Double {
    return if (n.toInt() == 1) {
        0.0
    } else {
        1.0 - ((6.0 * sum).toDouble()) / ((n * (n * n - 1)).toDouble())
    }
}

fun main() {
    val n = readln().toLong()
    val d = mutableListOf<Pair<Long, Long>>()

    repeat(n.toInt()) {
        val (x1, x2) = readln().split(" ").map { it.toLong() }
        d.add(x1 to x2)
    }

    val r1 = d.sortedBy { it.first }.mapIndexed { ind, v -> v.first to (ind+ 1).toLong() }.toMap()
    val r2 = d.sortedBy { it.second }.mapIndexed { ind, v -> v.second to (ind + 1).toLong() }.toMap()

    val dif = d.map { (r1[it.first]!! - r2[it.second]!!)}
    val sum = dif.sumOf { it * it }

    System.out.printf(Locale.US,"%.7f%n", formula(sum, n));
}