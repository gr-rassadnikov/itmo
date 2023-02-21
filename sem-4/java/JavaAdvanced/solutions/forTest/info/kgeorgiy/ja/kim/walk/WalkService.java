package info.kgeorgiy.ja.kim.walk;

import java.io.*;
import java.nio.file.Files;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Arrays;
import java.util.HexFormat;

import static java.nio.charset.StandardCharsets.UTF_8;

public class WalkService extends WalkCredentialValidator {
    private static final MessageDigest DIGEST;
    private static final String ERROR_CODE = "0".repeat(64);

    static {
        try {
            DIGEST = MessageDigest.getInstance("SHA-256");
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }
    }

    public static void run(
            final File inputFile,
            final File outputFile
    ) {
        try (final BufferedReader bufferedReader = new BufferedReader(new FileReader(inputFile, UTF_8))) {
            try {
                Files.createDirectories(outputFile.toPath().getParent());
            } catch (Exception e) {
                error("Unexpected error", outputFile, e.getMessage());
            }
            try (final BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(outputFile, UTF_8))) {
                String fileNameFromInputFile;
                while ((fileNameFromInputFile = bufferedReader.readLine()) != null) {
                    handle(fileNameFromInputFile, bufferedWriter);
                }
            } catch (IOException exception) {
                error("Cannot open output file", outputFile, exception.getMessage());
            }
        } catch (IOException e) {
            error("Cannot open input file", inputFile, e.getMessage());
        }
    }

    private static void handle(
            final String fileName,
            final BufferedWriter bufferedWriter
    ) {
        dfs(new File(fileName), bufferedWriter);
    }

    private static void dfs
            (
                    final File file,
                    final BufferedWriter bufferedWriter
            ) {

//        easy
        if (file.isDirectory() && file.listFiles() != null && file.listFiles().length > 0) {
            Arrays.stream(file.listFiles()).forEach(
                    /* effectively-final */ children -> dfs(children, bufferedWriter)
            );
        } else {
            writeHash(file, bufferedWriter);
        }

        //hard
//        if (file.isDirectory() && file.listFiles() != null) {
//            Arrays.stream(file.listFiles()).forEach(
//                    /* effectively-final */ children -> dfs(children, bufferedWriter)
//            );
//        } else {
//            writeHash(file, bufferedWriter);
//        }
    }

    private static void writeHash(
            final File file,
            final BufferedWriter bufferedWriter
    ) {
        try {
            if (valid(file)) {
                bufferedWriter.write("%s %s\n".formatted(toHex(sha256(file)), file.toString()));
            } else {
                error("Invalid file", file.toString(), "cannot read file");
                bufferedWriter.write("%s %s\n".formatted(ERROR_CODE, file.toString()));
            }
        } catch (IOException exception) {
            error("Cannot write to file", file, exception.getMessage());
        }
    }

    private static byte[] sha256(final File file) {
        try (final FileInputStream stream = new FileInputStream(file)) {
            final byte[] bytes = new byte[1 << 16];
            for (int toRead = stream.read(bytes); toRead != -1; toRead = stream.read(bytes)) {
                DIGEST.update(bytes, 0, toRead);
            }
        } catch (IOException exception) {
            error("Cannot read file", file, exception.getMessage());
        }

        return DIGEST.digest();
    }

    private static String toHex(final byte[] bytes) {
        return HexFormat.of().formatHex(bytes);
    }

    private static boolean valid(final File file) {
        return file.isFile() && file.canRead() && file.exists();
    }
}
