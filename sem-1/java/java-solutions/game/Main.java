package game;

import java.util.Scanner;

import game.MNKPlayers.*;

public class Main {
    public static void main(String[] args) {
        TicTacToeBoard board = new TicTacToeBoard(10, 7, 4);
        final int result = new TwoPlayerGame(
                board,
                new RandomPlayer(),
                new HumanPlayer(new Scanner(System.in))
        ).play(true);
        switch (result) {
            case 1:
                System.out.println("First player won");
                break;
            case 2:
                System.out.println("Second player won");
                break;
            case 0:
                System.out.println("Draw");
                break;
            default:
                throw new AssertionError("Unknown result " + result);
        }
    }
}
