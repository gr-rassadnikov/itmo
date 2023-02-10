import java.util.Scanner;

public class B {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        Long number = -25000L;
        for (int i = 0; i < n; i++) {
            System.out.println(number * 710);
            number++;

        }
    }
}