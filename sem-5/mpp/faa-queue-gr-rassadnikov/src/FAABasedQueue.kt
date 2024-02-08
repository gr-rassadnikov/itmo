import java.util.concurrent.atomic.*

/**
 * @author Rassadnikov Grigorii
 *
 */

class FAABasedQueue<E> : Queue<E> {
    private val head: AtomicReference<Segment>
    private val tail: AtomicReference<Segment>
    private val enqIdx: AtomicLong
    private val deqIdx: AtomicLong

    init {
        val dummy = Segment(0)
        head = AtomicReference(dummy)
        tail = AtomicReference(dummy)
        enqIdx = AtomicLong(0)
        deqIdx = AtomicLong(0)
    }

    override fun enqueue(element: E) {
        while (true) {
            val curTail = tail.get()
            val enqOfTail = curTail.enqIdx.getAndIncrement()
            if (checkSegmentSize(enqOfTail)) {
                val new = Segment(curTail.id + 1)
                val newEnq = new.enqIdx.getAndIncrement()
                new.cells[newEnq.toInt()] = element
                if (curTail.next.compareAndSet(null, new)) {
                    tail.compareAndSet(curTail, new)
                    return
                } else {
                    tail.compareAndSet(curTail, curTail.next.get())
                    continue
                }
            }
            if (curTail.cells.compareAndSet(enqOfTail.toInt(), null, element)) {
                return
            }
        }
    }

    @Suppress("UNCHECKED_CAST")
    override fun dequeue(): E? {
        while (true) {
            val curHead = head.get()
            val deqOfHead = curHead.deqIdx.getAndIncrement()
            if (checkSegmentSize(deqOfHead)) {
                if (curHead.next.get() == null) return null
                head.compareAndSet(curHead, curHead.next.get())
                continue
            }
            if (curHead.cells.compareAndSet(deqOfHead.toInt(), null, POISONED)) {
                continue
            }
            shouldTryToDequeue()
            val result = curHead.cells.get(deqOfHead.toInt())
            curHead.cells.set(deqOfHead.toInt(), null)
            return result as E?
        }
    }

    private fun checkSegmentSize(i: Long): Boolean {
        return i >= SEGMENT_SIZE
    }

    private fun shouldTryToDequeue(): Boolean {
        while (true) {
            val curDeqIdx = head.get().deqIdx.get()
            val curEnqIdx = tail.get().enqIdx.get()
            if (curDeqIdx != head.get().deqIdx.get()) continue
            return curDeqIdx < curEnqIdx
        }
    }
}

private class Segment(val id: Long) {
    val next = AtomicReference<Segment?>(null)
    val cells = AtomicReferenceArray<Any?>(SEGMENT_SIZE)
    val enqIdx = AtomicLong(0)
    val deqIdx = AtomicLong(0)
}

// DO NOT CHANGE THIS CONSTANT
private const val SEGMENT_SIZE = 2
