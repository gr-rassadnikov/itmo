package info.kgeorgiy.ja.kim.walk;

import java.io.File;
import java.util.Arrays;

public class Walk extends WalkService {
    public static void main(String[] args) {
        if (args == null || args.length != 2 || args[0] == null || args[1] == null) {
            error("Invalid arguments length", "", args == null ? "null" : Arrays.toString(args));
            return;
        }

        final File inputFile = new File(args[0]);
        final File outputFile = new File(args[1]);

        run(inputFile, outputFile);
    }
}
