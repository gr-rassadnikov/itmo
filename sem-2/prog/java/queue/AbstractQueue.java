package queue;

import java.util.Objects;
import java.util.function.*;
import java.util.*;

public abstract class AbstractQueue implements Queue {
    protected int start = 0;
    protected int end = -1;


    @Override
    public void enqueue(final Object element) {
        end++;
        Objects.requireNonNull(element);
        enqueueImpl(element);
    }

    protected abstract void enqueueImpl(Object element);

    @Override
    public Object dequeue() {
        assert end - start >= 0;
        start++;
        return dequeueImpl();
    }

    protected abstract Object dequeueImpl();

    @Override
    public int size() {
        return this.end - this.start + 1;
    }

    @Override
    public boolean isEmpty() {
        return this.end - this.start < 0;
    }

    @Override
    public Object element() {
        assert end - start >= 0;
        return elementImpl();
    }

    protected abstract Object elementImpl();

    @Override
    public void clear() {
        start = 0;
        end = -1;
        clearImpl();
    }

    protected abstract void clearImpl();


    @Override
    public int lastIndexIf(Predicate<Object> pred) {
        return 0;
    }

    @Override
    public int indexIf(Predicate<Object> pred) {
        return 0;
    }

}
