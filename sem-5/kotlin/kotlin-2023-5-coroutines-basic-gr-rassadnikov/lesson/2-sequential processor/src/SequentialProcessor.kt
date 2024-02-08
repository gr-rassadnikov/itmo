import kotlinx.coroutines.*

class SequentialProcessor(private val handler: (String) -> String) : TaskProcessor {
    @OptIn(ExperimentalCoroutinesApi::class, DelicateCoroutinesApi::class)
    private val dispatcher = newSingleThreadContext("handlerSingleThread")
    override suspend fun process(argument: String): String {
        val deferredResult = CoroutineScope(dispatcher).async {
            handler(argument)
        }
        return deferredResult.await()
    }
}
