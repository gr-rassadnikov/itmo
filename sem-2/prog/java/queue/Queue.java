package queue;

import java.util.function.Predicate;
import java.lang.*;
import java.util.*;

public interface Queue {
    void enqueue(Object element);

    Object dequeue();

    int size();

    boolean isEmpty();

    Object element();

    void clear();

    int lastIndexIf(Predicate<Object> pred);

    int indexIf(Predicate<Object> pred);
}
