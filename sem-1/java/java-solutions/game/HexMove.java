package game;

import com.sun.security.jgss.GSSUtil;

public class HexMove {
    private int row;
    private int col;
    private Cell value;

    public int getEnd() {
        return end;
    }

    private int end;

    public HexMove(int row, int col, Cell value, int end) {
        this.row = row;
        this.col = col;
        this.value = value;
        this.end = end;
    }

    public int getRow() {
        return row;
    }

    public int getCol() {
        return col;
    }

    public Cell getValue() {
        return value;
    }

    public void convertMoveToTicTac(int n) {
        int ind = n - 1;
        for (int i = 0; i < n; i++) {
            int loc_ind = ind;
            for (int j = 0; j < n; j++) {
                if (i + j == row && loc_ind == col) {
                    row = i;
                    col = j;
                    break;
                }
                loc_ind++;
            }
            ind--;
        }
    }

    public void convertMoveToHex(int n) {

        boolean fl = false;
        for (int c1 = 0; c1 < 2 * n - 1; c1 += 1) {
            for (int c2 = c1 % 2; c2 < 2 * n - 1; c2 += 2) {
                int rowc = c1;
                int colc = c2;
                int ind = n - 1;
                for (int i = 0; i < n; i++) {
                    int loc_ind = ind;
                    for (int j = 0; j < n; j++) {
                        if (i + j == rowc && loc_ind == colc) {
                            rowc = i;
                            colc = j;
                            break;
                        }
                        loc_ind++;
                    }
                    ind--;
                }
                if (rowc == row && colc == col) {
                    row = c1;
                    col = c2;

                    fl = true;
                    break;
                }
            }
            if (fl) {
                break;
            }
        }
    }

    @Override
    public String toString() {
        convertMoveToHex(11);
        return String.format("Move(%s, %d, %d)", value, row + 1, col + 1);
    }
}
