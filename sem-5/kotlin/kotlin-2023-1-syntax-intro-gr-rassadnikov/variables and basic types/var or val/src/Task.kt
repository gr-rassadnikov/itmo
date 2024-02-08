fun playerTurn(turnNumber: Int): Int {
    /* var or val */ playersCount: Int = 4
    return (turnNumber % playersCount)
}

fun factorial(n: Int): Int {
    /* var or val */ ans: Int = 1
    for (i in 2..n) {
        ans *= i
    }
    return ans
}
