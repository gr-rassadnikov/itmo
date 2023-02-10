package game;

import java.util.Arrays;
import java.util.Map;

class TicTacToeBoard implements Board, Position {
    private static final Map<Cell, String> CELL_TO_STRING = Map.of(
            Cell.E, ".",
            Cell.X, "X",
            Cell.O, "0"
    );

    public Cell[][] getField() {
        return field;
    }

    private final Cell[][] field;
    private Cell turn;

    public int getM() {
        return m;
    }

    private int m;

    public int getN() {
        return n;
    }

    private int n;

    public int getK() {
        return k;
    }

    private int k;


    public TicTacToeBoard(int m, int n, int k) {
        this.m = m;
        this.n = n;
        this.k = k;
        field = new Cell[m][n];
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
    public GameResult makeMove(TicTacMove move) {
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

    public GameResult makeMove(HexMove move) {
        return null;
    }

    private boolean checkDraw() {
        int count = 0;
        for (int r = 0; r < m; r++) {
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

    private boolean checkWin(TicTacMove move) {
        int cntRow = -1;
        for (int i = move.getRow(); i < m; i++) {
            if (field[i][move.getCol()] != turn) {
                break;
            }
            cntRow++;
        }
        for (int i = move.getRow(); i >= 0; i--) {
            if (field[i][move.getCol()] != turn) {
                break;
            }
            cntRow++;
        }
        if (cntRow >= k) {
            return true;
        }

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
        if (cntCol >= k) {
            return true;
        }

        int cntDiagNormal = -1;
        for (int i = 0; move.getRow() + i < m && move.getCol() + i < n; i++) {
            if (field[move.getRow() + i][move.getCol() + i] != turn) {
                break;
            }
            cntDiagNormal++;
        }
        for (int i = 0; move.getRow() - i >= 0 && move.getCol() - i >= 0; i++) {
            if (field[move.getRow() - i][move.getCol() - i] != turn) {
                break;
            }
            cntDiagNormal++;
        }
        if (cntDiagNormal >= k) {
            return true;
        }

        int cntDiagUnNormal = -1;
        for (int i = 0; move.getRow() + i < m && move.getCol() - i >= 0; i++) {
            if (field[move.getRow() + i][move.getCol() - i] != turn) {
                break;
            }
            cntDiagUnNormal++;
        }
        for (int i = 0; move.getRow() - i >= 0 && move.getCol() + i < n; i++) {
            if (field[move.getRow() - i][move.getCol() + i] != turn) {
                break;
            }
            cntDiagUnNormal++;
        }
        if (cntDiagUnNormal >= k) {
            return true;
        }


        return false;

    }

    public boolean isValid(final TicTacMove move) {
        return 0 <= move.getRow() && move.getRow() < m
                && 0 <= move.getCol() && move.getCol() < n
                && field[move.getRow()][move.getCol()] == Cell.E
                && turn == move.getValue();
    }

    public boolean isValid(final HexMove move) {
        return false;
    }

    @Override
    public Cell getCell(int row, int column) {
        return field[row][column];
    }

    @Override
    public String toString() {
        final StringBuilder sb = new StringBuilder(" ");
        for (Integer i = 0; i < n; i++) {
            sb.append(i + 1);
        }
        sb.append(System.lineSeparator());
        for (int r = 0; r < m; r++) {
            sb.append(r + 1);
            for (Cell cell : field[r]) {
                sb.append(CELL_TO_STRING.get(cell));
            }
            sb.append(System.lineSeparator());
        }
        sb.setLength(sb.length() - System.lineSeparator().length());
        return sb.toString();
    }
}
