package queue;

import static queue.ArrayQueueADT.*;

public class ArrayQueueAdtTestm {
    public static void main(String[] args) {
        ArrayQueueADT queue1 = new ArrayQueueADT();
        ArrayQueueADT queue2 = new ArrayQueueADT();

        for (int i = 0; i < 10; i++) {
            enqueue(queue1, "q1__" + i);
            enqueue(queue2, "q2__" + i);
        }
        System.out.println(size(queue1));
        System.out.println(element(queue1));
        clear(queue1);

        while (!isEmpty(queue1)) {
            System.out.println(dequeue(queue1));
        }
        while (!isEmpty(queue2)) {
            System.out.println(dequeue(queue2));
        }

    }
}
