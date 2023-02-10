import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;
import java.lang.*;

public class M {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);


        int t = scanner.nextInt();
        for (int c = 0; c < t; c++) {
            HashMap<Integer, Integer> stat = new HashMap<>();
            int n = scanner.nextInt();
            int[] a = new int[n];
            for (int i = 0; i < n; i++) {
                a[i] = scanner.nextInt();
            }
            int ans = 0;
            for (int j = n - 1; j >= 1; j--) {

                for (int i = 0; i <= j - 1; i++) {
                    int cntIn = 0;
                    if (stat.containsKey(2 * a[j] - a[i])) {
                        ans += stat.get(2 * a[j] - a[i]);
                    }
                }
                if (stat.containsKey(a[j])) {
                    stat.put(a[j], stat.get(a[j]) + 1);
                } else {
                    stat.put(a[j], 1);
                }
            }
            System.out.println(ans);
        }
    }
}