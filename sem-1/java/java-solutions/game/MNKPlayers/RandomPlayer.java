package game.MNKPlayers;

import java.util.Random;

import game.*;

public class RandomPlayer implements Player {
    private final Random random = new Random();

    public int getN() {
        return n;
    }

    public void setN(int n) {
        this.n = n;
    }

    int n;

    public int getM() {
        return m;
    }

    public void setM(int m) {
        this.m = m;
    }

    int m;
    Player rival;

    public void setRival(Player rival) {
        this.rival = rival;
    }
/*
    public RandomPlayer(TicTacToeBoard board) {
        this.m = board.getM();
        this.n = board.getN();
    }

 */

    public boolean wantDraw() {
        return random.nextBoolean();
    }


    @Override
    public TicTacMove makeMove(Position position, Cell[][] field) {
        while (true) {
            boolean tellDraw = random.nextBoolean();
            if (tellDraw) {
                if (rival.wantDraw()) {
                    return new TicTacMove(-2, -2, position.getTurn());
                }
            }
            final TicTacMove move = new TicTacMove(
                    random.nextInt(m),
                    random.nextInt(n),
                    position.getTurn()
            );
            if (position.isValid(move)) {
                return move;
            }
        }
    }
}
