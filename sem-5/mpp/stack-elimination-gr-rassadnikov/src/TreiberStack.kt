import java.util.concurrent.atomic.AtomicReference

/**
 * @author Rassadnikov Grigorii
 */
class TreiberStack<E> : Stack<E> {
    // Initially, the stack is empty.
    private val top = AtomicReference<Node<E>?>(null)

    override fun push(element: E) {
        while (true) {
            val curTop = top.get()
            val newTop = Node(element, curTop)
            if (CAS(top, curTop, newTop)) return
        }
    }

    override fun pop(): E? {
        while (true) {
            val curTop = top.get() ?: return null
            val newTop = curTop.next
            if (CAS(top, curTop, newTop)) {
                return curTop.element
            }
        }
    }

    private fun <E> CAS(link: AtomicReference<Node<E>?>, expectedValue: Node<E>?, newValue: Node<E>?) =
        link.compareAndSet(expectedValue, newValue)

    private class Node<E>(
        val element: E,
        val next: Node<E>?
    )
}
