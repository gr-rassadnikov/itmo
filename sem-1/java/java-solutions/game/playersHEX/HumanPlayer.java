package game.playersHEX;

;

import game.*;

import java.util.Scanner;

public class HumanPlayer implements Player {
    int n;

    public int getN() {
        return n;
    }

    public void setN(int n) {
        this.n = n;
    }

    private final Scanner in;
    Player rival;

    public void setRival(Player rival) {
        this.rival = rival;
    }

    public HumanPlayer(Scanner in) {
        this.in = in;
    }

    @Override
    public HexMove makeMove(Position position, Cell[][] field) {

        System.out.println("You want surrender? (YES/NO)");
        String end = in.next();
        if (end.equals("YES")) {
            return new HexMove(-1, -1, position.getTurn(), -1);
        }
        System.out.println("You want tell draw? (YES/NO)");
        String tellDraw = in.next();
        if (tellDraw.equals("YES")) {
            if (rival.wantDraw()) {
                System.out.println("Rival agree draw");
                return new HexMove(-2, -2, position.getTurn(), -2);
            } else {
                System.out.println("Rival disagree draw");
            }
        }
        System.out.println();
        System.out.println("Current position");
        System.out.println(position);
        System.out.println("Enter you move for " + position.getTurn());
        int moveRow;
        int moveCol;
        String input = in.next();

        try {
            moveRow = Integer.parseInt(input) - 1;
        } catch (NumberFormatException e) {
            System.out.println("uncorrect enter");
            return new HexMove(-3, -3, position.getTurn(), -3);
        }
        input = in.next();
        try {
            moveCol = Integer.parseInt(input) - 1;
        } catch (NumberFormatException e) {
            System.out.println("uncorrect enter");
            return new HexMove(-3, -3, position.getTurn(), -3);
        }

        if (!checkCorrect(moveRow, moveCol, field)) {
            System.out.println("Your move is uncorrect, please make new move");
            input = in.next();

            try {
                moveRow = Integer.parseInt(input) - 1;
            } catch (NumberFormatException e) {
                System.out.println("uncorrect enter");
                return new HexMove(-3, -3, position.getTurn(), -3);
            }
            input = in.next();
            try {
                moveCol = Integer.parseInt(input) - 1;
            } catch (NumberFormatException e) {
                System.out.println("uncorrect enter");
                return new HexMove(-3, -3, position.getTurn(), -3);
            }
        }
        if (!checkCorrect(moveRow, moveCol, field)) {
            System.out.println("Your move is uncorrect again, you loose");
            return new HexMove(-3, -3, position.getTurn(), -3);
        }
        return new HexMove(moveRow, moveCol, position.getTurn(), 1);
    }


    boolean checkCorrect(int moveRow, int moveCol, Cell[][] field) {
        if (moveCol < 0 || moveRow < 0 || moveRow >= 2 * n - 1 || moveCol >= 2 * n - 1 ||
                moveCol % 2 != moveRow % 2) {
            return false;
        }
        int ind = n - 1;
        for (int i = 0; i < n; i++) {
            int loc_ind = ind;
            for (int j = 0; j < n; j++) {
                if (i + j == moveRow && loc_ind == moveCol) {
                    if (field[i][j] != Cell.E) {
                        return false;
                    } else {
                        return true;
                    }
                }
                loc_ind++;
            }
            ind--;
        }
        return false;
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



