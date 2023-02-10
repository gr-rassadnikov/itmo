package queue;

import java.util.Arrays;
import java.util.Objects;
import java.util.Arrays;
import java.util.Objects;
import java.util.function.Predicate;
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

Pred: queue != null
Post: n' = n && immutable(n) && R = n
    size

Pred: queue != null
Post: n' = n && immutable(n) && && R == (n == 0)
    isEmpty

Pred: queue != null
Post: n = n' = 0
    clear

Pred:value!=null && queue != null
Post: n' = n && immutable(n) && (predicate.test(v.element)) && v- first
    indexIf

Pred:value!=null && queue != null
Post: n' = n && immutable(n) && (predicate.test(v.element)) && v- last
    lastindexIf

 */

public class LinkedQueue extends AbstractQueue {
    private Node startNode = null;
    private Node endNode = null;

    @Override
    public void enqueueImpl(final Object element) {

        if (startNode == null) {
            startNode = new Node(element, null);
            endNode = startNode;
        } else {
            Node wasEnd = endNode;
            endNode = new Node(element, null);
            wasEnd.prev = endNode;
        }
    }

    @Override
    protected Object dequeueImpl() {
        Object result = startNode.element;
        startNode = startNode.prev;
        return result;
    }

    @Override
    protected Object elementImpl() {
        return startNode.element;
    }


    @Override
    protected void clearImpl() {
        startNode = null;
        endNode = null;
    }

    @Override
    public int indexIf(Predicate<Object> predicate) {
        return indexIfImpl(predicate, "first");
    }

    @Override
    public int lastIndexIf(Predicate<Object> predicate) {
        return indexIfImpl(predicate, "last");
    }

    private int indexIfImpl(Predicate<Object> predicate, String type) {
        int index = -1;
        int result = -1;
        Node v = startNode;
        while (v != null) {
            index++;
            if (predicate.test(v.element)) {
                if (type.equals("first")) {
                    if (result == -1) {
                        result = index;
                    }
                } else {
                    result = index;
                }
            }
            v = v.prev;
        }
        return result;
    }

    private static class Node {
        private final Object element;
        private Node prev;

        public Node(Object element, Node prev) {
            this.element = element;
            this.prev = prev;
        }
    }

}
