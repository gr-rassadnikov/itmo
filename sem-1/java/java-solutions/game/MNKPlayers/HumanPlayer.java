package game.MNKPlayers;

import java.util.Scanner;

import game.*;

public class HumanPlayer implements Player {
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

    private final Scanner in;
    Player rival;

    public void setRival(Player rival) {
        this.rival = rival;
    }

    public HumanPlayer(Scanner in) {
        this.in = in;

    }

    @Override
    public TicTacMove makeMove(Position position, Cell[][] field) {
        System.out.println();
        System.out.println("Current position");
        System.out.println(position);
        System.out.println("You want surrender? (YES/NO)");
        String end = in.next();
        if (end.equals("YES")) {
            return new TicTacMove(-1, -1, position.getTurn());
        }
        System.out.println("You want tell draw? (YES/NO)");
        String tellDraw = in.next();
        if (tellDraw.equals("YES")) {
            if (rival.wantDraw()) {
                System.out.println("Rival agree draw");
                return new TicTacMove(-2, -2, position.getTurn());
            } else {
                System.out.println("Rival disagree draw");
            }
        }

        System.out.println("Enter you move for " + position.getTurn());
        String input = in.next();
        int moveRow;
        int moveCol;
        try {
            moveRow = Integer.parseInt(input) - 1;
        } catch (NumberFormatException e) {
            System.out.println("uncorrect enter");
            return new TicTacMove(-3, -3, position.getTurn());
        }
        input = in.next();
        try {
            moveCol = Integer.parseInt(input) - 1;
        } catch (NumberFormatException e) {
            System.out.println("uncorrect enter");
            return new TicTacMove(-3, -3, position.getTurn());
        }
        if (!checkCorrect(moveRow, moveCol, field)) {
            System.out.println("Your move is uncorrect, please make new move");
            input = in.next();

            try {
                moveRow = Integer.parseInt(input) - 1;
            } catch (NumberFormatException e) {
                System.out.println("uncorrect enter");
                return new TicTacMove(-3, -3, position.getTurn());
            }
            input = in.next();
            try {
                moveCol = Integer.parseInt(input) - 1;
            } catch (NumberFormatException e) {
                System.out.println("uncorrect enter");
                return new TicTacMove(-3, -3, position.getTurn());
            }
        }
        if (!checkCorrect(moveRow, moveCol, field)) {
            System.out.println("Your move is uncorrect again, you loose");
            return new TicTacMove(-3, -3, position.getTurn());
        }
        return new TicTacMove(moveRow, moveCol, position.getTurn());
    }

    boolean checkCorrect(int moveRow, int moveCol, Cell[][] field) {
        if (moveCol < 0 || moveRow < 0 || moveRow >= m || moveCol >= n || field[moveRow][moveCol] != Cell.E) {
            return false;
        }
        return true;
    }

    @Override
    public boolean wantDraw() {
        System.out.println("Rival tell you draw (YES/NO)");
        String wantDraw = in.next();
        if (wantDraw.equals("YES")) {
            return true;
        }
        return false;
    }
}

