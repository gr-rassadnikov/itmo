import kotlin.math.sqrt

fun failNegativeValue() {
    throw ArithmeticException("sqrt with negative value")
}

fun checkedSqrt(x: Double): Double {
    if (x >= 0.0) {
        return sqrt(x)
    }
    failNegativeValue()
}