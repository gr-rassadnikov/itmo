import kotlin.math.abs
import kotlin.math.sqrt

fun main() {
    val (n, k) = readln().split(" ").map { it.toInt() }
    val categories = readln().split(" ").map { it.toInt() }
    val numericValues = readln().split(" ").map { it.toDouble() }

    val oneHotCategories = Array(n) { i -> DoubleArray(k) { j -> if (categories[i] == j + 1) 1.0 else 0.0 } }

    val correlations = DoubleArray(k) { i ->
        val correlation = pearsonCorrelation(oneHotCategories.map { it[i] }.toDoubleArray(), numericValues.toDoubleArray())
        abs(correlation)
    }

    val weightedSum = correlations.mapIndexed { index, correlation ->
        correlation * categories.count { it == index + 1 }
    }.sum()

    val weightedAvgCorrelation = weightedSum / n
    println("%.9f".format(weightedAvgCorrelation))
}

fun pearsonCorrelation(x: DoubleArray, y: DoubleArray): Double {
    require(x.size == y.size) { "Arrays must have the same size" }

    val n = x.size
    val sumX = x.sum()
    val sumY = y.sum()
    val sumSquareX = x.sumByDouble { it * it }
    val sumSquareY = y.sumByDouble { it * it }
    val sumXY = x.zip(y).sumByDouble { (a, b) -> a * b }

    val numerator = n * sumXY - sumX * sumY
    val denominator = sqrt((n * sumSquareX - sumX * sumX) * (n * sumSquareY - sumY * sumY))

    if (denominator == 0.0) {
        return 0.0
    }

    return numerator / denominator
}