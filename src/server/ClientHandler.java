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
                    socket.getInputStream()
                )
            );

            out = new PrintWriter(
                socket.getOutputStream(),
                true
            );

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
                    + message
                );

                processMessage(message);
            }

        } catch (IOException e) {

            System.out.println(
                "Cliente desconectado."
            );

        } finally {

            try {

                if (socket != null) {
                    socket.close();
                }

            } catch (IOException e) {

                e.printStackTrace();
            }
        }
    }

    private void processMessage(
        String message
    ) {

        if (message.startsWith(
            "ALIEN_KILLED")) {

            int points = 10;

            try {

                String[] parts =
                    message.split(" ");

                if (parts.length > 1) {

                    points =
                        Integer.parseInt(
                            parts[1]
                        );
                }

            } catch (Exception e) {

                points = 10;
            }

            gameState.alienKilled(
                points
            );

            out.println(
                "UPDATE_SCORE "
                + gameState.getPlayerScore()
            );

            out.println(
                "SPEED "
                + gameState.getSpeed()
            );
        }

        else if (
            message.equals(
                "PLAYER_HIT"
            )
        ) {

            gameState.playerHit();

            out.println(
                "UPDATE_LIVES "
                + gameState.getPlayerLives()
            );
        }

        else if (
            message.equals(
                "NEXT_ROUND"
            )
        ) {

            gameState.nextRoundServer();

            out.println(
                "SPEED "
                + gameState.getSpeed()
            );
        }

        else if (
            message.equals(
                "PLAYER_LOSE"
            )
        ) {

            System.out.println(
                "Jugador perdió la partida."
            );
        }

        else if (
            message.equals(
                "REQUEST_UFO"
            )
        ) {

            out.println(
                "CREATE_UFO LEFT_RIGHT "
                + gameState.generateUfoPoints()
            );
        }
    }
}