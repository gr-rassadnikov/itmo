import kotlinx.coroutines.*

fun CoroutineScope.runApplication(
    runUI: suspend () -> Unit,
    runApi: suspend () -> Unit,
) {
    val jobApi = launch {
        while (true) {
            try {
                runApi.invoke()
                break
            } catch (e: CancellationException) {
                println("Warning: runApi was interrupted by runUI. ${e.message}")
                break
            } catch (_: Exception) {
                continue
            }
        }
    }

    try {
        launch {
            runUI.invoke()
        }
    } catch (e: Exception) {
        println("Error: runUI was end with error. ${e.message}")
        jobApi.cancel()
        throw e
    }
}
