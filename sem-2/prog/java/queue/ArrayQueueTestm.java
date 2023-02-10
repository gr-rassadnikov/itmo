package queue;


public class ArrayQueueTestm {
    public static void main(String[] args) {
        ArrayQueue queue1 = new ArrayQueue();
        ArrayQueue queue2 = new ArrayQueue();

        for (int i = 0; i < 10; i++) {
            queue1.enqueue("q1_" + i);
            queue2.enqueue("q2_" + i);
        }
        System.out.println(queue1.size());
        System.out.println(queue1.element());
        queue1.clear();

        while (!queue1.isEmpty()) {
            System.out.println(queue1.dequeue());
        }
        while (!queue2.isEmpty()) {
            System.out.println(queue2.dequeue());
        }

    }
}
