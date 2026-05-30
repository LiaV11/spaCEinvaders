package src.server;

import java.net.ServerSocket;
import java.net.Socket;
import java.io.IOException;

public class GameServer {

    private int port;

    public GameServer(int port) {

        this.port = port;
    }

    public void start() {

        ServerSocket serverSocket = null;

        try {

            serverSocket =
                new ServerSocket(port);

            System.out.println(
                "Servidor iniciado en puerto "
                + port
            );

            while (true) {

                Socket client =
                    serverSocket.accept();

                System.out.println(
                    "Cliente conectado: "
                    + client.getInetAddress()
                );

                ClientHandler handler =
                    new ClientHandler(
                        client
                    );

                Thread thread =
                    new Thread(handler);

                thread.start();
            }

        } catch (IOException e) {

            e.printStackTrace();

        } finally {

            try {

                if (
                    serverSocket != null
                ) {
                    serverSocket.close();
                }

            } catch (IOException e) {

                e.printStackTrace();
            }
        }
    }
}