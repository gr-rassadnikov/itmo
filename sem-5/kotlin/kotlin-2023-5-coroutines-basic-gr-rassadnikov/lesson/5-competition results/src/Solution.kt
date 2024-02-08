import kotlin.time.Duration
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.map

fun Flow<Cutoff>.resultsFlow(): Flow<Results> {
    val storage = mutableMapOf<String, Duration>()
    return this.map { cutoff ->
        storage[cutoff.number] = cutoff.time
        Results(storage)
    }
}
