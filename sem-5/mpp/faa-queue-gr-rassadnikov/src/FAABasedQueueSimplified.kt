import java.util.concurrent.atomic.*
import kotlin.math.*

/**
 * @author Rassadnikov Grigorii
 */
class FAABasedQueueSimplified<E> : Queue<E> {
    private val infiniteArray = AtomicReferenceArray<Any?>(1024) // conceptually infinite array
    private val enqIdx = AtomicLong(0)
    private val deqIdx = AtomicLong(0)

    override fun enqueue(element: E) {
        while (true) {
            val i = enqIdx.getAndIncrement().toInt()
            if (infiniteArray.compareAndSet(i, null, element)) {
                return
            }
        }
    }

    @Suppress("UNCHECKED_CAST")
    override fun dequeue(): E? {
        while (true) {
            if (deqIdx.get() >= enqIdx.get()) return null
            val i = deqIdx.getAndIncrement().toInt()
            if (infiniteArray.compareAndSet(i, null, POISONED)) {
                continue
            }
            val result = infiniteArray.get(i) as E
            infiniteArray[i] = null
            return result
        }
    }

    private fun <E> CAS(link: AtomicReference<E>, expectedValue: E?, newValue: E?): Boolean {
        if (link.get() != expectedValue) return false
        link.set(newValue)
        return true
    }

    override fun validate() {
        for (i in 0 until min(deqIdx.get().toInt(), enqIdx.get().toInt())) {
            check(infiniteArray[i] == null || infiniteArray[i] == POISONED) {
                "`infiniteArray[$i]` must be `null` or `POISONED` with `deqIdx = ${deqIdx.get()}` at the end of the execution"
            }
        }
        for (i in max(deqIdx.get().toInt(), enqIdx.get().toInt()) until infiniteArray.length()) {
            check(infiniteArray[i] == null || infiniteArray[i] == POISONED) {
                "`infiniteArray[$i]` must be `null` or `POISONED` with `enqIdx = ${enqIdx.get()}` at the end of the execution"
            }
        }
    }

}

val POISONED = Any()
