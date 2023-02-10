package game;

import java.util.Scanner;

import game.playersHEX.*;

public class MainHEX {
    public static void main(String[] args) {
        HexBoard board = new HexBoard(11);
        final int result = new HexTwoPlayerGame(
                board,
                new RandomPlayer(),
                //new CheatingPlayer()
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
