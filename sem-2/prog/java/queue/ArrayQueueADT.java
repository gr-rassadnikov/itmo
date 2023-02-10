package queue;

import java.util.Arrays;
import java.util.Objects;

/*
Model: q[1]...1[n]
Invariant: n>=0 && for i=1..n : q[i] != null

Let immutable(n): for i=1...n q'[i] = q[i]

Pred: element!=null && queue != null
Post: n' = n + 1 && q[n'] = element && immutable(n)
    enqueue(element)

Pred:n>=1  && queue != null
Post: n' = n-1 && immutable(n') && R = q[1]
    dequeue

Pred:n>=1 && queue != null
Post: n' = n && immutable(n) && R = q[1]
    element

Pred:true && queue != null
Post: n' = n && immutable(n) && R = n
    size

Pred:true && queue != null
Post: n' = n && immutable(n) && && R == (n == 0)
    isEmpty

Pred:true && queue != null
Post: n = n' = 0
    clear

Pred:value!=null && queue != null
Post: n' = n && immutable(n) && (q[R+1] = value || R = -1) && R- min
    indexOf

Pred:value!=null && queue != null
Post: n' = n && immutable(n) && (q[R+1] = value || R = -1) && R- max
    lastIndexOf

 */
public class ArrayQueueADT {
    private Object[] elements = new Object[2];
    private int start = 0;
    private int end = -1;


    public ArrayQueueADT() {
    }


    public static void enqueue(final ArrayQueueADT queue, final Object element) {
        Objects.requireNonNull(element);
        queue.end++;
        ensureCapacity(queue);
        queue.elements[queue.end] = element;
    }

    public static Object dequeue(final ArrayQueueADT queue) {
        assert queue.end - queue.start >= 0;
        Object result = queue.elements[queue.start];
        queue.elements[queue.start] = null;
        queue.start++;
        return result;
    }

    public static Object element(final ArrayQueueADT queue) {
        assert queue.end - queue.start >= 0;
        return queue.elements[queue.start];
    }

    public static int size(final ArrayQueueADT queue) {
        return queue.end - queue.start + 1;
    }

    public static boolean isEmpty(final ArrayQueueADT queue) {
        return queue.end - queue.start < 0;
    }

    public static void clear(final ArrayQueueADT queue) {
        queue.elements = new Object[2];
        queue.start = 0;
        queue.end = -1;
    }

    public static int indexOf(final ArrayQueueADT queue, final Object value) {
        for (int i = queue.start; i <= queue.end; i++) {
            if (queue.elements[i].equals(value)) {
                return i - queue.start;
            }
        }
        return -1;
    }

    public static int lastIndexOf(final ArrayQueueADT queue, final Object value) {
        for (int i = queue.end; i >= queue.start; i--) {
            if (queue.elements[i].equals(value)) {
                return i - queue.start;
            }
        }
        return -1;
    }


    private static void ensureCapacity(final ArrayQueueADT queue) {
        if (queue.elements.length <= queue.end) {
            queue.elements = Arrays.copyOf(Arrays.copyOfRange(queue.elements, queue.start, queue.end + 1)
                    , (queue.end - queue.start + 1) * 2);
            int copyStart = queue.start;
            queue.start = 0;
            queue.end = queue.end - copyStart;
        }
    }


}
