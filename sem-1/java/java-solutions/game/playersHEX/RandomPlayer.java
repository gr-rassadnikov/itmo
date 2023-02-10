package game.playersHEX;

;

import java.util.Random;

import game.*;

public class RandomPlayer implements Player {
    private final Random random = new Random();
    int n;
    Player rival;

    public int getN() {
        return n;
    }

    public void setN(int n) {
        this.n = n;
    }

    public void setRival(Player rival) {
        this.rival = rival;
    }

    public boolean wantDraw() {
        return random.nextBoolean();
    }


    @Override
    public HexMove makeMove(Position position, Cell[][] field) {
        while (true) {
            boolean tellDraw = random.nextBoolean();
            if (tellDraw) {
                if (rival.wantDraw()) {
                    return new HexMove(-2, -2, position.getTurn(), -2);
                }
            }
            final HexMove move = new HexMove(
                    random.nextInt(n),
                    random.nextInt(n),
                    position.getTurn(),
                    1
            );
            if (position.isValid(move)) {
                return move;
            }
        }
    }
}
