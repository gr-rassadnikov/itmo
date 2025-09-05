import java.util.*
import kotlin.math.abs

fun main() {
    val n = readln().toInt()
    val objects = List(n) {
        val (x, y) = readln().split(" ").map { it.toInt() }
        x to y
    }

    val m = readln().toInt()
    repeat(m) {
        val (x, k) = readln().split(" ").map { it.toInt() }
        val dist = objects.map { (xi, yi) -> abs(xi - x) to yi }.toMutableList()

        dist.sortBy { it.first }
        val f = dist.take(k)

        if (k >= dist.size || dist[k - 1] != dist[k]) {
            val avg = f.map { it.second }.average()
            System.out.printf(Locale.US,"%.7f%n", avg);
        } else {
            println(-1.0)
        }
    }
}