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
        try {
            ServerSocket serverSocket = new ServerSocket(port);

            System.out.println("Servidor iniciado en puerto " + port);

            while (true) {
                Socket client = serverSocket.accept();

                System.out.println("Cliente conectado.");

                ClientHandler handler =
                        new ClientHandler(client);

                new Thread(handler).start();
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}