import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;
import java.lang.Integer;

public class K {

    static boolean GOGO(long x, long y, int n) {
        long b[] = new long[5];


        for (int i = 0; i < n - 1; i++) {
            if ((x & (1 << i)) == 0) b[1] = 0;
            else b[1] = 1;
            if ((x & (1 << i + 1)) == 0) b[2] = 0;
            else b[2] = 1;
            if ((y & (1 << i)) == 0) b[3] = 0;
            else b[3] = 1;
            if ((y & (1 << i + 1)) == 0) b[4] = 0;
            else b[4] = 1; 
            if ((b[1] == b[2]) && (b[2] == b[3]) && (b[3] == b[4])) {
                return false;
            }
        }

        return true;
    }

    static int YouOnlyLiveNice(int n, int m) {
        int res = 0;
        int len = 1 << n;
        long a[][] = new long[m][len];
        long dp[][] = new long[len][len];

        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len; j++) {
                if (GOGO(i, j, n)) {
                    dp[i][j] = 1;
                } else {
                    dp[i][j] = 0;
                }
            }
        }

        for (int i = 0; i < len; i++) {
            a[0][i] = 1;
        }

        for (int x = 1; x < m; x++) {
            for (int i = 0; i < len; i++) {
                for (int j = 0; j < len; j++) {
                    a[x][i] = a[x][i] + a[x - 1][j] * dp[j][i];
                }
            }
        }
        for (int i = 0; i < len; i++) {
            res += a[m - 1][i];
        }
        return res;
    }

    public static void main(String[] args) throws IOException {
        Scanner scanner = new Scanner(System.in);
        FileWriter fileWriter = new FileWriter(new File("nice.out"));

        int n = scanner.nextInt();
        int m = scanner.nextInt();

        if (n > m) {
            int tmp = n;
            n = m;
            m = tmp;
        }
        for (int ii=1;ii<=30;ii++){
            for (int jj=1;jj<=30;jj++){
                if (ii*jj<=30){
                    int i=ii;
                    int j=jj;
                    if (i > j) {
                        int tmp = i;
                        i = j;
                        j = tmp;
                    }
                    System.err.print(i);
                    System.err.print("  ");
                    System.err.println(j);
                    fileWriter.write(Integer.toString(i)+Integer.toString(j)+" :" +Integer.toString(YouOnlyLiveNice(i, j)) + ",\n");
                }

            }
        }
        fileWriter.write(YouOnlyLiveNice(n, m) + "");
        fileWriter.flush();
    }
}
