import java.util.Scanner;

public class J {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        int graph[][] = new int[n][n];
        for (int i = 0; i < n; i++) {
            String input = scanner.next();
            for (int j = 0; j < n; j++) {
                graph[i][j] = input.charAt(j) - '0';
            }
        }
        int ans[][] = new int[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (graph[i][j] != 0) {
                    ans[i][j] = 1;
                    for (int k = j + 1; k < n; k++) {
                        graph[i][k] -= graph[j][k];
                        graph[i][k] %= 10;
                    }
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                System.out.print(ans[i][j]);
            }
            System.out.println();
        }


    }
}
