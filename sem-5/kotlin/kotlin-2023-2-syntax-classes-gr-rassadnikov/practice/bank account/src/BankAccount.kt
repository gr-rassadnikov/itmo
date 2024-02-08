class BankAccount(private val amount: Int) {
    var balance = amount
        private set
    init {
        checkCorrectAmount()
    }

    fun deposit(amount: Int) = changeBalanceByAddValue(amount) {it}

    fun withdraw(amount: Int) = changeBalanceByAddValue(amount) {-it}

    private fun changeBalanceByAddValue(amount: Int, add: (Int) -> Int) {
        checkCorrectAmount(amount)
        val last = balance
        balance += add(amount)
        checkCorrectAmount()
        logTransaction(last, balance)
    }

    @Throws
    private fun checkCorrectAmount(amount: Int = balance) {
        if (amount <= 0) throw IllegalArgumentException("Incorrect amount")
    }

}
