import java.util.*;
import java.lang.*;

public class IntList {
    int[] mas = new int[0];
    int now = 0;

    public void add(Integer x) {
        if (this.now >= mas.length) {
            this.mas = Arrays.copyOf(this.mas, 2 * this.mas.length + 1);
        }
        mas[this.now] = x;
        this.now++;
    }

    public int size() {
        return now;
    }

    public int get(int i) {
        return mas[i];
    }

}
