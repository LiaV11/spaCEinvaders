package src.utils;

public class MessageParser {

    public static String parse(
            String message) {

        String[] parts =
                message.split(" ");

        return parts[0];
    }
}