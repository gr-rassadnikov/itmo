package game;

public interface Position {
    Cell getTurn();

    boolean isValid(HexMove move);

    boolean isValid(TicTacMove move);

    Cell getCell(int row, int column);
}
