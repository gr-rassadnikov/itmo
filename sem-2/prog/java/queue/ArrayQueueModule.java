package queue;

import java.util.Arrays;
import java.util.Objects;

/*
Model: q[1]...1[n]
Invariant: n>=0 && for i=1..n : q[i] != null

Let immutable(n): for i=1...n q'[i] = q[i]

Pred: element!=null
Post: n' = n + 1 && q[n'] = element && immutable(n)
    enqueue(element)

Pred:n>=1
Post: n' = n-1 && immutable(n') && R = q[1]
    dequeue

Pred:n>=1
Post: n' = n && immutable(n) && R = q[1]
    element

Pred:true
Post: n' = n && immutable(n) && R = n
    size

Pred:true
Post: n' = n && immutable(n) && && R == (n == 0)
    isEmpty

Pred:true
Post: n = n' = 0
    clear

Pred:value!=null
Post: n' = n && immutable(n) && (q[R+1] = value || R = -1) && R- min
    indexOf

Pred:value!=null
Post: n' = n && immutable(n) && (q[R+1] = value || R = -1) && R- max
    lastIndexOf

 */
public class ArrayQueueModule {
    private static Object[] elements = new Object[2];
    private static int start = 0;
    private static int end = -1;

    public static void enqueue(final Object element) {
        Objects.requireNonNull(element);
        end++;
        ensureCapacity();
        elements[end] = element;
    }

    public static Object dequeue() {
        assert end - start >= 0;
        Object result = elements[start];
        elements[start] = null;
        start++;
        return result;
    }

    public static Object element() {
        assert end - start >= 0;
        return elements[start];
    }

    public static int size() {
        return end - start + 1;
    }

    public static boolean isEmpty() {
        return end - start < 0;
    }

    public static void clear() {
        elements = new Object[2];
        start = 0;
        end = -1;
    }

    public static int indexOf(Object value) {
        for (int i = start; i <= end; i++) {
            if (elements[i].equals(value)) {
                return i - start;
            }
        }
        return -1;
    }

    public static int lastIndexOf(Object value) {
        for (int i = end; i >= start; i--) {
            if (elements[i].equals(value)) {
                return i - start;
            }
        }
        return -1;
    }


    private static void ensureCapacity() {
        if (elements.length <= end) {
            elements = Arrays.copyOf(Arrays.copyOfRange(elements, start, end + 1)
                    , (end - start + 1) * 2);
            int copyStart = start;
            start = 0;
            end = end - copyStart;
        }
    }


}
