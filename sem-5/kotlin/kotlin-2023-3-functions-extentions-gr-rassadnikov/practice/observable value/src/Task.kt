interface Value<T> {
    @set:Throws
    var value: T
    @Throws
    fun observe(function: (T) -> Unit): Cancellation<T>
}

class Cancellation<T>(private var observerValue: MutableValue<T>) {
    fun cancel() {
        observerValue.resetAction(this)
    }
}

class MutableValue<T>(val initial: T) : Value<T> {
    class ObserveValueException(message: String? = null, cause: Throwable? = null) : Exception(message, cause)

    private var subscribers: MutableMap<Cancellation<T>?, ((T) -> Unit)?> = mutableMapOf()

    @Throws
    override fun observe(function: (T) -> Unit): Cancellation<T> {
        runFunctionWithValue(function, value)
        val cancellation = Cancellation(observerValue = this)
        subscribers[cancellation] = function
        return cancellation
    }

    @set:Throws
    override var value: T = initial
        set(value) {
            for (function in subscribers.values) {
                if (function != null) {
                    runFunctionWithValue(function, value)
                }
            }
            field = value
        }

    fun resetAction(cancellation: Cancellation<T>) {
        subscribers.remove(cancellation)
    }

    private fun runFunctionWithValue(function: (T) -> Unit, value: T) {
        try {
            function(value)
        } catch (e: Exception) {
            throw ObserveValueException(
                "Can't observe or get value, completion function get error: ${e.message}",
                e.cause
            )
        }
    }
}
