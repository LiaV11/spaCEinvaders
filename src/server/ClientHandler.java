package src.server;

import java.io.*;
import java.net.Socket;

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

    public void sendMessage(String message) {

        out.println(message);
    }

    private void broadcast(String message) {

        for (ClientHandler client
             : GameServer.clients) {

            client.sendMessage(message);
        }
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

        /*
        ALIEN KILLED
        */

        if (message.startsWith(
            "ALIEN_KILLED")) {

            int alienId = 0;
            int points = 10;

            try {

                String[] parts =
                    message.split(" ");

                alienId =
                    Integer.parseInt(
                        parts[1]
                    );

                points =
                    Integer.parseInt(
                        parts[2]
                    );

            } catch (Exception e) {

                alienId = 0;
                points = 10;
            }

            gameState.alienKilled(
                alienId,
                points
            );

            broadcast(
                "ALIEN_DIED "
                + alienId
            );

            broadcast(
                "UPDATE_SCORE "
                + gameState.getPlayerScore()
            );

            broadcast(
                "SPEED "
                + gameState.getSpeed()
            );
        }

        /*
        PLAYER HIT
        */

        else if (
            message.equals(
                "PLAYER_HIT"
            )
        ) {

            gameState.playerHit();

            broadcast(
                "UPDATE_LIVES "
                + gameState.getPlayerLives()
            );
        }

        /*
        NEXT ROUND
        */

        else if (
            message.equals(
                "NEXT_ROUND"
            )
        ) {

            gameState.nextRoundServer();

            broadcast(
                "SPEED "
                + gameState.getSpeed()
            );
        }

        /*
        PLAYER LOSE
        */

        else if (
            message.equals(
                "PLAYER_LOSE"
            )
        ) {

            System.out.println(
                "Jugador perdió la partida."
            );

            broadcast("PLAYER_LOSE");
        }

        /*
        UFO
        */

        else if (
            message.equals(
                "REQUEST_UFO"
            )
        ) {

            int points =
                gameState.generateUfoPoints();

            broadcast(
                "CREATE_UFO LEFT_RIGHT "
                + points
            );
        }

        /*
        PLAYER POSITION
        */

        else if (
            message.startsWith(
                "PLAYER_POS"
            )
        ) {

            broadcast(message);
        }

        /*
        BULLETS
        */

        else if (
            message.startsWith(
                "BULLET"
            )
        ) {

            broadcast(message);
        }
    }
}