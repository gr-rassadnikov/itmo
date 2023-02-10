import java.io.*;
import java.lang.*;

class MyScan {
    Reader reader = new InputStreamReader(System.in);
    int ch;
    char[] buffer = new char[2048];
    int indInBuffer = buffer.length;

    public int getCh() {
        try {
            if (indInBuffer == buffer.length) {
                for (int i = 0; i < buffer.length; i++) {
                    buffer[i] = 0;
                }
                if (reader.read(buffer) == -1) {
                    return -1;
                }
                indInBuffer = 0;
            }
            if ((int) buffer[indInBuffer] == 0) {
                indInBuffer++;
                return -1;
            }
            return buffer[indInBuffer++];

        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
        return 0;
    }

    public int nextInt() {
        StringBuilder strBuilder = new StringBuilder();
        int flag = 0;
        while (true) {
            if (flag == 1 && !Character.isDigit(ch)) {
                break;
            }
            if (Character.isDigit(ch)) {
                strBuilder.append((char) ch);
                flag = 1;
            }
            ch = getCh();
        }
        return Integer.parseInt(strBuilder.toString());
    }
}

public class H {
    public static void main(String[] args) {
        MyScan scanner = new MyScan();
        int n = scanner.nextInt();
        int a[] = new int[n];
        int sumPref[] = new int[n];
        int maxA = 0;
        int sum = 0;
        for (int i = 0; i < n; i++) {
            a[i] = scanner.nextInt();
            maxA = Integer.max(maxA, a[i]);
            sum += a[i];
            sumPref[i] = sum;
        }
        int numberOfTranz[] = new int[sum + 1];
        int cntBlocks = 0;
        int localMax = 0;
        for (int i = 0; i <= sum; i++) {
            if (i >= localMax + a[cntBlocks]) {
                localMax += a[cntBlocks];
                cntBlocks++;
                if (cntBlocks > n) {
                    cntBlocks = n - 1;
                }
            }
            numberOfTranz[i] = cntBlocks - 1;
        }
        int q = scanner.nextInt();
        int statAnswer[] = new int[sum + 1];
        int t;
        for (int i = 0; i < q; i++) {
            t = scanner.nextInt();
            if (t < maxA) {
                System.out.println("Impossible");
            } else if (statAnswer[t] > 0) {
                System.out.println(statAnswer[t]);
            } else {
                int ind = numberOfTranz[t];
                int nowElement = sumPref[ind];
                int ans = 1;
                while (nowElement < sum) {
                    ans++;
                    if (nowElement + t >= sum) {
                        break;
                    }
                    if (numberOfTranz[nowElement + t] >= n) {
                        break;
                    }
                    ind = numberOfTranz[nowElement + t];
                    nowElement = sumPref[ind];
                }
                System.out.println(ans);
                statAnswer[t] = ans;

            }
        }
    }
}
