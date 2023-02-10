package game;

import game.MNKPlayers.*;

public class TwoPlayerGame {
    private final Board board;
    private final Player player1;
    private final Player player2;

    public TwoPlayerGame(Board board, Player player1, Player player2) {

        this.board = board;
        this.player1 = player1;
        this.player2 = player2;
        this.player1.setN(board.getN());
        this.player1.setM(board.getM());
        this.player2.setN(board.getN());
        this.player2.setM(board.getM());
        this.player1.setRival(this.player2);
        this.player2.setRival(this.player1);

    }

    public int play(boolean log) {
        while (true) {
            final int result1 = makeMove(player1, 1, log);
            if (result1 != -1) {
                return result1;
            }
            final int result2 = makeMove(player2, 2, log);
            if (result2 != -1) {
                return result2;
            }
        }
    }

    private int makeMove(Player player, int no, boolean log) {
        final TicTacMove move = player.makeMove(board.getPosition(), board.getField());
        GameResult result = board.makeMove(move);
        if (log) {
            System.out.println();
            if (move.getRow() == -1 && move.getCol() == -1) {
                System.out.println("Player " + no + " Сдалался");
                System.out.println(board);
            } else if (move.getRow() == -2 && move.getCol() == -2) {
                System.out.println(board);
                result = GameResult.DRAW;
                System.out.println("Result: " + result);
            } else if (move.getRow() == -3 && move.getCol() == -3) {
                System.out.println(board);
                System.out.println("Result: " + result);
            } else {
                System.out.println("Player: " + no);
                System.out.println(move);
                System.out.println(board);
                System.out.println("Result: " + result);
            }
        }
        switch (result) {
            case WIN:
                return no;
            case LOOSE:
                return 3 - no;
            case DRAW:
                return 0;
            case UNKNOWN:
                return -1;
            default:
                throw new AssertionError("Unknown makeMove result " + result);
        }
    }
}
