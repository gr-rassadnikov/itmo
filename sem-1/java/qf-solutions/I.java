import java.util.Scanner;

public class I {
    public static void main(String[] args) {
        int n;
        Scanner scanner = new Scanner(System.in);
        n = scanner.nextInt();
        Integer xRight = Integer.MIN_VALUE, xLeft = Integer.MAX_VALUE, yRight = Integer.MIN_VALUE, yLeft = Integer.MAX_VALUE;

        for (int i = 0; i < n; i++) {
            Integer x, y, h;
            x = scanner.nextInt();
            y = scanner.nextInt();
            h = scanner.nextInt();
            xRight = Integer.max(x + h, xRight);
            xLeft = Integer.min(x - h, xLeft);
            yLeft = Integer.min(y - h, yLeft);
            yRight = Integer.max(y + h, yRight);
        }
        Integer h = (Integer.max(xRight - xLeft, yRight - yLeft) + 1) / 2;

        System.out.print((xLeft + xRight) / 2);
        System.out.print(" ");
        System.out.print((yLeft + yRight) / 2);
        System.out.print(" ");
        System.out.print(h);
    }
}
