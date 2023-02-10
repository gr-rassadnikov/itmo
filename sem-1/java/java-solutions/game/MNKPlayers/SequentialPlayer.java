package game.MNKPlayers;

import java.util.*;

import game.*;

public class SequentialPlayer implements Player {
    Player rival;

    public void setRival(Player rival) {
        this.rival = rival;
    }

    public boolean wantDraw() {
        return true;
    }

    public int getN() {
        return 0;
    }

    public void setN(int n) {
    }

    public int getM() {
        return 0;
    }

    public void setM(int m) {
    }

    @Override
    public TicTacMove makeMove(Position position, Cell[][] field) {
        for (int r = 0; r < 3; r++) {
            for (int c = 0; c < 3; c++) {
                boolean tellDraw = new Random().nextBoolean();
                if (tellDraw) {
                    if (rival.wantDraw()) {
                        return new TicTacMove(-2, -2, position.getTurn());
                    }
                }
                final TicTacMove move = new TicTacMove(r, c, position.getTurn());
                if (position.isValid(move)) {
                    return move;
                }
            }
        }
        throw new AssertionError("No valid moves");
    }
}
