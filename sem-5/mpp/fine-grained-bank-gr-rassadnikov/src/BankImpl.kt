import java.util.concurrent.locks.ReentrantLock
import kotlin.concurrent.withLock

/**
 * Bank implementation.
 *
 * @author : Rassadnikov Grigorii
 */
class BankImpl(n: Int) : Bank {
    private val accounts: Array<Account> = Array(n) { Account() }

    override val numberOfAccounts: Int
        get() = accounts.size

    /**
     *
     */
    override fun getAmount(index: Int): Long {
        accounts[index].lock()
        val amount = accounts[index].amount
        accounts[index].unlock()
        return amount
    }

    /**
     *
     */
    override val totalAmount: Long
        get() {
            accounts.forEach { account -> account.lock() }
            val sum = accounts.sumOf { account ->
                account.amount
            }
            accounts.forEach { account -> account.unlock() }
            return sum
        }

    /**
     *
     */
    override fun deposit(index: Int, amount: Long): Long {
        require(amount > 0) { "Invalid amount: $amount" }
        val account = accounts[index]
        return account.withLock {
            check(!(amount > Bank.MAX_AMOUNT || account.amount + amount > Bank.MAX_AMOUNT)) { "Overflow" }
            account.amount += amount
            account.amount
        }
    }

    /**
     *
     */
    override fun withdraw(index: Int, amount: Long): Long {
        require(amount > 0) { "Invalid amount: $amount" }
        val account = accounts[index]
        return account.withLock {
            check(account.amount - amount >= 0) { "Underflow" }
            account.amount -= amount
            account.amount
        }
    }

    /**
     *
     */
    override fun transfer(fromIndex: Int, toIndex: Int, amount: Long) {
        require(amount > 0) { "Invalid amount: $amount" }
        require(fromIndex != toIndex) { "fromIndex == toIndex" }
        val from = accounts[fromIndex]
        val to = accounts[toIndex]
        if (fromIndex < toIndex) {
            accounts[fromIndex].withLock {
                accounts[toIndex].withLock {
                    check(amount <= from.amount) { "Underflow" }
                    check(!(amount > Bank.MAX_AMOUNT || to.amount + amount > Bank.MAX_AMOUNT)) { "Overflow" }
                    from.amount -= amount
                    to.amount += amount
                }
            }
        } else {
            accounts[toIndex].withLock {
                accounts[fromIndex].withLock {
                    check(amount <= from.amount) { "Underflow" }
                    check(!(amount > Bank.MAX_AMOUNT || to.amount + amount > Bank.MAX_AMOUNT)) { "Overflow" }
                    from.amount -= amount
                    to.amount += amount
                }
            }
        }
    }

    /**
     * Private account data structure.
     */
    class Account {
        /**
         * Amount of funds in this account.
         */
        var amount: Long = 0
        private val lock = ReentrantLock()

        fun lock() = lock.lock()

        fun unlock() = lock.unlock()

        fun <T> withLock(action: () -> T) = lock.withLock { action.invoke() }
    }
}
