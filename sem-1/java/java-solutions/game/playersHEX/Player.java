package game.playersHEX;

import game.*;

public interface Player {
    HexMove makeMove(Position position, Cell[][] field);

    void setRival(Player rival);

    boolean wantDraw();

    void setN(int n);

    int getN();
}
