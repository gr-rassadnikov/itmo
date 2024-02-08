import java.util.concurrent.atomic.*

/**
 * @author Rassadnikov Grigorii
 */

class Solution(private val env: Environment) : Lock<Solution.Node> {
    private val node = AtomicReference<Node>()

    override fun lock(): Node {
        val newNode = Node(isLock = AtomicReference(true)) // сделали узел

        val curNode = node.getAndSet(newNode)
        if (curNode != null) {
            curNode.nextNode.getAndSet(newNode)
            while (newNode.isLock.get()) env.park()
        }
        return newNode // вернули узел
    }

    override fun unlock(node: Node) {
        if (node.nextNode.get() == null && this.node.compareAndSet(node, null)) {
            return
        } else {
            while (true) {
                if (node.nextNode.get() != null) {
                    break
                }
            }
            node.nextNode.get().isLock.value = false
            env.unpark(node.nextNode.get().thread)
        }
    }

    class Node(val isLock: AtomicReference<Boolean> = AtomicReference(false)) {
        val thread = Thread.currentThread() // запоминаем поток, которые создал узел
        val nextNode = AtomicReference<Node>()
    }
}