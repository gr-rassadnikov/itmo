import java.util.concurrent.atomic.*

/**
 * @author Rassadnikov Grigorii
 *
 */
class MSQueue<E> : Queue<E> {
    private val head: AtomicReference<Node<E>>
    private val tail: AtomicReference<Node<E>>

    init {
        val dummy = Node<E>(null)
        head = AtomicReference(dummy)
        tail = AtomicReference(dummy)
    }

    override fun enqueue(element: E) {
        val newNode = Node(element)
        while (true) {
            val curTail = tail.get()
            if (CAS(curTail.next, null, newNode)) {
                tail.compareAndSet(curTail, newNode)
                return
            } else {
                tail.compareAndSet(curTail, curTail.next.get())
            }
        }
    }

    override fun dequeue(): E? {
        while (true) {
            val curHead = head.get()
            val curTail = tail.get()
            val curHeadNext = curHead.next.get() ?: return null
            if (curHead == curTail) {
                tail.compareAndSet(curTail, curHeadNext)
            } else if (head.compareAndSet(curHead, curHeadNext)) {
                val result = curHeadNext.element
                curHeadNext.element = null
                return result
            }
        }
    }

    // FOR TEST PURPOSE, DO NOT CHANGE IT.
    override fun validate() {
        check(tail.get().next.get() == null) {
            "At the end of the execution, `tail.next` must be `null`"
        }
        check(head.get().element == null) {
            "At the end of the execution, the dummy node shouldn't store an element"
        }
    }

    private fun <E> CAS(link: AtomicReference<Node<E>?>, expectedValue: Node<E>?, newValue: Node<E>?) =
        link.compareAndSet(expectedValue, newValue)

    private class Node<E>(
        var element: E?
    ) {
        val next = AtomicReference<Node<E>?>(null)
    }
}
