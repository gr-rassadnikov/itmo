package game.MNKPlayers;

import game.*;

public class CheatingPlayer implements Player {
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
        //final TicTacToeBoard board = (TicTacToeBoard) position;
        TicTacMove first = null;
        for (int r = 0; r < 3; r++) {
            for (int c = 0; c < 3; c++) {
                final TicTacMove move = new TicTacMove(r, c, position.getTurn());
                if (position.isValid(move)) {
                    if (first == null) {
                        first = move;
                    } else {
                        //board.makeMove(move);
                    }
                }

            }
        }
        return first;
    }
}
