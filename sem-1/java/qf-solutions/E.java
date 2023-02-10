import java.util.List;
import java.util.*;

public class E {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        int m = scanner.nextInt();
        List<List<Integer>> e = new ArrayList<>(n);
        for (int i = 0; i < n; i++) {
            List<Integer> t = new ArrayList<>();
            e.add(t);
        }
        int iscmd[] = new int[n];
        for (int i = 0; i < n - 1; i++) {
            int u = scanner.nextInt();
            int v = scanner.nextInt();
            u--;
            v--;
            List<Integer> t = e.get(u);
            t.add(v);
            e.set(u, t);
            List<Integer> t2 = e.get(v);
            t2.add(u);
            e.set(v, t2);


        }
        int c[] = new int[m];
        for (int i = 0; i < m; i++) {
            int u = scanner.nextInt();
            iscmd[--u] = 1;
            c[i] = u;
        }
        int d[] = new int[n];
        int ind = 0;
        List<Integer> q = new ArrayList<>();
        q.add(c[0]);
        d[c[0]] = 0;
        int u;
        int used[] = new int[n];
        used[c[0]] = 1;
        while (ind < q.size()) {
            u = q.get(ind);
            ind++;
            for (Integer i : e.get(u)) {
                if (used[i] != 1) {
                    used[i] = 1;
                    d[i] = d[u] + 1;
                    q.add(i);
                }
            }
        }
        int h = 0;
        for (int i = 0; i < n; i++) {
            if (iscmd[i] == 1 && d[i] > h) {
                h = d[i];
            }
        }
        //System.out.println(h);
        if (h % 2 == 1) {
            System.out.println("NO");
        } else {
            int med = h / 2;
            List<Integer> W = new ArrayList<>();
            for (int i = 0; i < n; i++) {
                if (d[i] == med) {
                    W.add(i);
                    break;
                }
            }
            for (int k = 0; k < W.size(); k++) {
                int flag = 1;
                int x = W.get(k);
                int ind2 = 0;
                List<Integer> q2 = new ArrayList<>();
                q2.add(x);
                int u2;
                int d2[] = new int[n];
                d2[x] = 0;
                int used2[] = new int[n];
                used2[x] = 1;
                while (ind2 < q2.size()) {
                    u2 = q2.get(ind2);
                    ind2++;
                    for (Integer i : e.get(u2)) {
                        if (used2[i] != 1) {
                            used2[i] = 1;
                            d2[i] = d2[u2] + 1;
                            q2.add(i);
                        }
                    }
                }
                int rast = -1;
                for (int i = 0; i < n; i++) {
                    if (rast >= 0 && d2[i] != rast && iscmd[i] == 1) {
                        flag = 0;
                        break;
                    } else if (rast == -1 && iscmd[i] == 1) {
                        rast = d2[i];
                    }
                }
                if (flag == 1) {
                    System.out.println("YES");
                    System.out.println(x + 1);
                    return;
                }
            }
            System.out.println("NO");

        }


    }
}
