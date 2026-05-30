package src.utils;

public class MessageParser {

    public static String parse(
        String message
    ) {

        if (
            message == null ||
            message.isEmpty()
        ) {
            return "";
        }

        String[] parts =
            message.split(" ");

        return parts[0];
    }
}