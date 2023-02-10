package queue;


public class ArrayQueueModuleTestm {
    public static void main(String[] args) {
        for (int i = 0; i < 10; i++) {
            ArrayQueueModule.enqueue(i);
        }
        for (int i = 0; i < 10; i++) {
            ArrayQueueModule.enqueue(i);
        }
        System.out.println(ArrayQueueModule.indexOf(5));
        System.out.println(ArrayQueueModule.lastIndexOf(5));
        while (!ArrayQueueModule.isEmpty()) {
            System.out.println(ArrayQueueModule.dequeue());
        }
    }

}

