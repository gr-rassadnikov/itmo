package game.playersHEX;

;

import game.*;

import java.util.Scanner;

public class CheatingPlayer implements Player {
    Player rival;

    public void setRival(Player rival) {
        this.rival = rival;
    }

    public int getN() {
        return 0;
    }

    public void setN(int n) {
    }

    @Override
    public HexMove makeMove(Position position, Cell[][] field) {
        //final HexBoard board = (HexBoard) position;
        HexMove first = null;
        for (int r = 0; r < 3; r++) {
            for (int c = 0; c < 3; c++) {
                final HexMove move = new HexMove(r, c, position.getTurn(), 1);
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

    @Override
    public boolean wantDraw() {
        System.out.println("Rival tell you draw (YES/NO)");
        //String wantDraw = in.next();

        return false;
    }
}
