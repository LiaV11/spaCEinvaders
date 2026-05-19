package src.server;

import java.net.Socket;
import java.io.*;
import src.game.GameState;

public class ClientHandler implements Runnable {

    private Socket socket;
    private BufferedReader in;
    private PrintWriter out;

    private static GameState gameState =
            new GameState();

    public ClientHandler(Socket socket) {
        this.socket = socket;

        try {
            in = new BufferedReader(
                    new InputStreamReader(
                            socket.getInputStream()));

            out = new PrintWriter(
                    socket.getOutputStream(),
                    true);

            sendInitialState();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void sendInitialState() {
        out.println("UPDATE_SCORE 0");
        out.println("UPDATE_LIVES 3");
        out.println("SPEED 1");
    }

    @Override
    public void run() {

        String message;

        try {
            while ((message = in.readLine()) != null) {

                System.out.println(
                        "Mensaje recibido: "
                                + message);

                processMessage(message);
            }

        } catch (IOException e) {
            System.out.println(
                    "Cliente desconectado.");
        }
    }

    private void processMessage(
            String message) {

        if (message.equals("ALIEN_KILLED")) {

            gameState.alienKilled();

            out.println(
                    "UPDATE_SCORE "
                            + gameState.getPlayerScore());

            out.println(
                    "SPEED "
                            + gameState.getSpeed());
        }

        if (message.equals("PLAYER_HIT")) {

            gameState.playerHit();

            out.println(
                    "UPDATE_LIVES "
                            + gameState.getPlayerLives());
        }

        if (message.equals("REQUEST_UFO")) {

            out.println(
                    "CREATE_UFO LEFT_RIGHT "
                            + gameState.generateUfoPoints());
        }
    }
}