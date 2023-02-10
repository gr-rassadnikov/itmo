package game;

interface Board {
    Position getPosition();

    GameResult makeMove(TicTacMove move);

    GameResult makeMove(HexMove move);

    Cell[][] getField();

    int getN();

    int getM();
}
