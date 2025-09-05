import java.util.*
import kotlin.math.roundToInt


fun main() {
    val T = arrayOf(doubleArrayOf(0.9, 0.1), doubleArrayOf(0.2, 0.8))
    val E = arrayOf(doubleArrayOf(0.1, 0.4, 0.4, 0.1), doubleArrayOf(0.3, 0.2, 0.2, 0.3))

    val scanner = Scanner(System.`in`)
    val str = scanner.next()
    val k = 2
    val n = str.length

    var O = mutableListOf<Int>()
    for (i in str) {
        if (i == 'A') O.add(0)
        if (i == 'G') O.add(1)
        if (i == 'C') O.add(2)
        if (i == 'T') O.add(3)

    }

    val V = Array(k) { DoubleArray(n) }

    V[0][0] = 0.5 * E[0][O[0]]
    V[1][0] = 0.5 * E[1][O[0]]

    for (i in 1 until n) {
        val result0 = DoubleArray(k) { V[it][i - 1] * T[it][0] * E[0][O[i]] }
        V[0][i] = result0.sum()

        val result1 = DoubleArray(k) { V[it][i - 1] * T[it][1] * E[1][O[i]] }
        V[1][i] = result1.sum()

    }

    val B = Array(k) { DoubleArray(n) }

    B[0][n - 1] = 1.0
    B[1][n - 1] = 1.0

    for (i in n - 2 downTo 0) {
        val result0 = DoubleArray(k) { B[it][i + 1] * T[0][it] * E[it][O[i + 1]] }
        B[0][i] = result0.sum()

        val result1 = DoubleArray(k) { B[it][i + 1] * T[1][it] * E[it][O[i + 1]] }
        B[1][i] = result1.sum()

    }


//    for (i in V) {
//        for (j in i) {
//            print(j.toString() + " ")
//        }
//        println()
//    }
//
//    for (i in B) {
//        for (j in i) {
//            print(j.toString() + " ")
//        }
//        println()
//    }
    val best = (V.map { it.last() }.sum())

    val P = (0 until n).map { ((V[0][it] * B[0][it] / best)) }

    for (i in P) {
        print("%.2f ".format(Locale.ENGLISH, i))
    }
    println()
    for (i in P) {
        print("%.2f ".format(Locale.ENGLISH, 1 - i))
    }


//    println(V.map { it.last() }.sum())
}
