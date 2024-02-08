package dijkstra

import java.util.*
import java.util.concurrent.Phaser
import java.util.concurrent.ThreadLocalRandom
import java.util.concurrent.atomic.AtomicInteger
import java.util.concurrent.locks.ReentrantLock
import kotlin.Comparator
import kotlin.concurrent.thread

/**
 * @author Rassadnikov Grigorii
 *
 */

private val NODE_DISTANCE_COMPARATOR = Comparator<Node> { o1, o2 -> Integer.compare(o1!!.distance, o2!!.distance) }

// Returns `Integer.MAX_VALUE` if a path has not been found.
fun shortestPathParallel(start: Node) {
    val workers = Runtime.getRuntime().availableProcessors()
    // The distance to the start node is `0`
    start.distance = 0
    // Create a priority (by distance) queue and add the start node into it
    val q = PMQueue(workers)
    q.push(start)
    // Run worker threads and wait until the total work is done
    val onFinish = Phaser(workers + 1) // `arrive()` should be invoked at the end by each worker
    val workIsDone = AtomicInteger(0)
    workIsDone.incrementAndGet()

    repeat(workers) {
        thread {
            while (true) {
                val cur: Node = q.pop() ?: if (workIsDone.get() <= 0) break else continue
                for (e in cur.outgoingEdges) {
                    var dist = e.to.distance
                    while (dist > cur.distance + e.weight) {
                        if (e.to.casDistance(dist, cur.distance + e.weight)) {
                            q.push(e.to)
                            workIsDone.incrementAndGet()
                            break
                        }
                        dist = e.to.distance
                    }
                }
                workIsDone.decrementAndGet()
            }
            onFinish.arrive()
        }
    }
    onFinish.arriveAndAwaitAdvance()
}

class PMQueue(private val workers: Int) {
    private val list = mutableListOf<PriorityQueue<Node>>()
    private val locks = mutableListOf<ReentrantLock>()

    init {
        for (i in 0 until workers) {
            list.add(PriorityQueue(workers, NODE_DISTANCE_COMPARATOR))
            locks.add(ReentrantLock())
        }
    }

    private fun randomCellIndex(): Int =
        ThreadLocalRandom.current().nextInt(workers)

    fun push(element: Node) {
        var index: Int?
        do {
            index = randomCellIndex()
        } while (index != null && !locks[index].tryLock())
        if (index != null) {
            list[index].add(element)
            locks[index].unlock()
        }
    }

    fun pop(): Node? {
        while (true) {
            val index1 = randomCellIndex()
            val index2 = randomCellIndex()

            val node1 = list[index1].peek()
            val node2 = list[index2].peek()

            val minPr: Int = if (node1 == null && node2 == null) {
                return null
            } else if (node1 == null) {
                index2
            } else if (node2 == null) {
                index2
            } else {
                if (NODE_DISTANCE_COMPARATOR.compare(node1, node2) < 0) {
                    index1
                } else {
                    index2
                }
            }

            if (locks[minPr].tryLock()) {
                return list[minPr].poll()
            }
        }
    }
}
