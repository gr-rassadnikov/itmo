package queue;

import java.util.Arrays;
import java.util.Objects;
import java.util.function.*;
import java.lang.*;
import java.util.*;

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
Post: n' = n && immutable(n) && (predicate.test(elements[R])) && R- min
    indexIf

Pred:value!=null && queue != null
Post: n' = n && immutable(n) && (predicate.test(elements[R])) && R- max
    lastindexIf

 */
public class ArrayQueue extends AbstractQueue {
    private Object[] elements = new Object[2];

    @Override
    public void enqueueImpl(final Object element) {
        ensureCapacity();
        elements[end] = element;
    }

    @Override
    protected Object dequeueImpl() {
        Object result = elements[start - 1];
        elements[start - 1] = null;
        return result;
    }

    @Override
    protected Object elementImpl() {
        return elements[start];
    }

    @Override
    protected void clearImpl() {
        this.elements = new Object[2];
    }

    @Override
    public int indexIf(Predicate<Object> predicate) {
        return indexIfImpl(predicate, this.start, this.end + 1, 1);
    }

    @Override
    public int lastIndexIf(Predicate<Object> predicate) {
        return indexIfImpl(predicate, this.end, this.start - 1, -1);
    }

    private int indexIfImpl(Predicate<Object> predicate, int from, int to, int step) {
        for (int i = from; i != to && i >= 0 && i < this.elements.length; i += step) {
            if (predicate.test(this.elements[i])) {
                return i - this.start;
            }
        }
        return -1;
    }

    public int indexOf(queue.ArrayQueue this, final Object value) {
        for (int i = this.start; i <= this.end; i++) {
            if (this.elements[i].equals(value)) {
                return i - this.start;
            }
        }
        return -1;
    }

    public int lastIndexOf(queue.ArrayQueue this, final Object value) {
        for (int i = this.end; i >= this.start; i--) {
            if (this.elements[i].equals(value)) {
                return i - this.start;
            }
        }
        return -1;
    }

    private void ensureCapacity() {
        if (elements.length <= end) {
            elements = Arrays.copyOf(Arrays.copyOfRange(elements, start, end + 1)
                    , (end - start + 1) * 2);
            int copyStart = start;
            start = 0;
            end = end - copyStart;
        }
    }
}
