import kotlin.coroutines.CoroutineContext
import kotlinx.coroutines.launch
import kotlinx.coroutines.withContext

class ParallelEvaluator {
    suspend fun run(task: Task, n: Int, context: CoroutineContext) {
        withContext(context) {
            for (i in 0..<n) {
                launch {
                    try {
                        task.run(i)
                    } catch (e: Exception) {
                        throw TaskEvaluationException(e)
                    }
                }
            }
        }
    }
}
