import java.lang.Exception

class NoResultProvided(message: String) : NoSuchElementException(message)
sealed interface IntResult {

    data class Ok(val value: Int) : IntResult
    data class Error(val reason: String) : IntResult

    fun getOrNull() = when (this) {
        is Ok -> value
        is Error -> null
    }

    fun getOrDefault(defaultValue: Int): Int = when (this) {
        is Ok -> value
        is Error -> defaultValue
    }

    fun getStrict(): Int = when(this) {
        is Ok -> value
        is Error -> throw NoResultProvided(message = reason)
    }

}

fun safeRun(function: () -> Int): IntResult {
    return try {
        val value = function()
        IntResult.Ok(value)
    } catch (e: Exception) {
        val reason = e.message ?: "unknown error"
        IntResult.Error(reason = reason)
    }
}
