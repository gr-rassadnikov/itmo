package game.MNKPlayers;

import game.*;

public interface Player {
    TicTacMove makeMove(Position position, Cell[][] field);

    void setRival(Player rival);

    boolean wantDraw();

    void setN(int n);

    void setM(int m);

    int getN();

    int getM();
}
