package info.kgeorgiy.ja.kim.walk;

public class WalkCredentialValidator {
    static <T, R> void error(
            final String message,
            final T info,
            final R reason
    ) {
        System.err.printf("%s: %s, caused by: %s.\n", message, info.toString(), reason.toString());
    }
}
