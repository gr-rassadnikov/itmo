package game;

import java.util.Arrays;
import java.util.Map;

class HexBoard implements Board, Position {

    private static final Map<Cell, String> CELL_TO_STRING = Map.of(
            Cell.E, ".",
            Cell.X, "X",
            Cell.O, "0",
            Cell.N, " "
    );

    public Cell[][] getField() {
        return field;
    }

    private Cell[][] field;
    private Cell turn;


    public int getN() {
        return n;
    }

    public int getM() {
        return 0;
    }

    int n;


    public HexBoard(int n) {

        this.n = n;

        field = new Cell[n][n];
        for (Cell[] row : field) {
            Arrays.fill(row, Cell.E);
        }
        turn = Cell.X;
    }

    @Override
    public Cell getTurn() {
        return turn;
    }

    @Override
    public Position getPosition() {
        return this;
    }

    @Override
    public GameResult makeMove(HexMove move) {
        if (!isValid(move)) {
            return GameResult.LOOSE;
        }

        field[move.getRow()][move.getCol()] = move.getValue();
        if (checkWin(move)) {
            return GameResult.WIN;
        }

        if (checkDraw()) {
            return GameResult.DRAW;
        }

        turn = turn == Cell.X ? Cell.O : Cell.X;
        return GameResult.UNKNOWN;
    }

    public GameResult makeMove(TicTacMove move) {
        return null;
    }


    private boolean checkDraw() {
        int count = 0;
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                if (field[r][c] == Cell.E) {
                    count++;
                }
            }
        }
        if (count == 0) {
            return true;
        }
        return false;
    }

    private boolean checkWin(HexMove move) {

        //for X
        int cntCol = -1;
        for (int i = move.getCol(); i < n; i++) {
            if (field[move.getRow()][i] != turn) {
                break;
            }
            cntCol++;
        }
        for (int i = move.getCol(); i >= 0; i--) {
            if (field[move.getRow()][i] != turn) {
                break;
            }
            cntCol++;
        }
        if (cntCol >= n && turn == Cell.X) {
            return true;
        }


        //for O
        int cntRow = -1;
        for (int i = move.getRow(); i < n; i++) {
            if (field[i][move.getCol()] != turn) {
                break;
            }
            cntRow++;
        }
        for (int i = move.getRow(); i >= 0; i--) {
            if (field[i][move.getRow()] != turn) {
                break;
            }
            cntRow++;
        }
        if (cntRow >= n && turn == Cell.O) {
            return true;
        }


        int cntDiagNormal = -1;
        for (int i = 0; i < n; i++) {
            if (field[i][i] != turn) {
                break;
            }
            cntDiagNormal++;
        }

        int cntDiagUnNormal = -1;
        for (int i = 0; i < n; i++) {
            if (field[n - i - 1][n - i - 1] != turn) {
                break;
            }
            cntDiagNormal++;
        }
        if (cntDiagUnNormal >= n || cntDiagNormal >= n) {
            return true;
        }

        return false;

    }

    public boolean isValid(final HexMove move) {
        return 0 <= move.getRow() && move.getRow() < n
                && 0 <= move.getCol() && move.getCol() < n
                && field[move.getRow()][move.getCol()] == Cell.E
                && turn == move.getValue();
    }

    public boolean isValid(TicTacMove move) {
        return false;
    }

    @Override
    public Cell getCell(int row, int column) {
        return field[row][column];
    }

    @Override
    public String toString() {
        Cell[][] print = new Cell[2 * n - 1][2 * n - 1];
        for (Cell[] row : print) {
            Arrays.fill(row, Cell.N);
        }
        int ind = n - 1;
        for (int i = 0; i < n; i++) {
            int loc_ind = ind;
            for (int j = 0; j < n; j++) {
                print[i + j][loc_ind] = field[i][j];
                loc_ind++;
            }
            ind--;
        }


        final StringBuilder sb = new StringBuilder(" ");
        for (Integer i = 0; i < 2 * n - 1; i++) {
            sb.append(i + 1);
            if (i < 9) {
                sb.append(" ");
            }
        }
        sb.append(System.lineSeparator());
        for (int r = 0; r < 2 * n - 1; r++) {
            sb.append(r + 1);
            if (r < 9) {
                sb.append(" ");
            }
            for (Cell cell : print[r]) {
                sb.append(CELL_TO_STRING.get(cell));
                sb.append(" ");

            }
            sb.append(System.lineSeparator());
        }
        sb.setLength(sb.length() - System.lineSeparator().length());
        return sb.toString();
    }
}
