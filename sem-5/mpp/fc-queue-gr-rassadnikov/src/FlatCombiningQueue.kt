import java.util.concurrent.*
import java.util.concurrent.atomic.*

class FlatCombiningQueue<E> : Queue<E> {
    private val queue = ArrayDeque<E>() // sequential queue
    private val combinerLock = AtomicBoolean(false) // unlocked initially
    private val tasksForCombiner = AtomicReferenceArray<Any?>(TASKS_FOR_COMBINER_SIZE)

    override fun enqueue(element: E) {
        if (combinerLock.compareAndSet(false, true)) {
            queue.addLast(element)
            takeLock()
        } else {
            while (true) {
                if (combinerLock.compareAndSet(false, true)) {
                    queue.addLast(element)
                    takeLock()
                    return
                }
            }
        }
    }

    @Suppress("UNCHECKED_CAST")
    override fun dequeue(): E? {
        if (combinerLock.compareAndSet(false, true)) {
            val result = queue.removeFirstOrNull()
            takeLock()
            return result
        } else {
            val cell = randomCellIndex()
            while (true) {
                if (tasksForCombiner.compareAndSet(cell, null, Dequeue)) {
                    break
                }
            }
            while (true) {
                val value = tasksForCombiner.get(cell)
                if (value is Result<*>) {
                    tasksForCombiner.set(cell, null)
                    return value.value as E?
                } else if (value == null) {
                    tasksForCombiner.set(cell, Dequeue)
                }
                if (combinerLock.compareAndSet(false, true)) {
                    takeLock()
                }
            }
        }
    }

    private fun takeLock() {
        for (i in 0 until TASKS_FOR_COMBINER_SIZE) {
            val value = tasksForCombiner[i]
            if (value == Dequeue) {
                val pop = queue.removeFirstOrNull()
                tasksForCombiner.set(i, Result(pop))
            }
        }
        combinerLock.set(false)
    }

    private fun randomCellIndex(): Int =
        ThreadLocalRandom.current().nextInt(tasksForCombiner.length())
}

private const val TASKS_FOR_COMBINER_SIZE = 3 // Do not change this constant!

private object Dequeue

private class Result<V>(
    val value: V
)