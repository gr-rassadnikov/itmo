import kotlin.math.acos

fun isEven(x: Int): Any {
    return x % 2 == 0
}

fun getPi(): Any {
    return acos(-1.0)
}

fun `21 hi`(): Any {
    return "hi".repeat(21)
}

fun maxLong(): Any {
    return 9223372036854775807L
}

fun twoPowers(n: Int): Any {
    val x = IntArray(n)
    x[0] = 1
    for (i in 1 until n) {
        x[i] = x[i - 1] * 2
    }
    return x
}

fun currentAge(): Any {
    return 20u
}
