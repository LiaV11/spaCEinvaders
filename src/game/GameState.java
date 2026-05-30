package src.game;

import java.util.ArrayList;
import java.util.Random;
import src.patterns.AlienFactory;

public class GameState {

    private Player player;
    private ArrayList<Alien> aliens;
    private ArrayList<Bunker> bunkers;
    private int speed;

    public GameState() {
        player = new Player();
        aliens = new ArrayList<>();
        bunkers = new ArrayList<>();
        speed = 1;

        createAliens();
        createBunkers();
    }

    private void createAliens() {

        aliens.clear();

        // 8 Squids
        for (int i = 0; i < 8; i++) {
            aliens.add(AlienFactory.createSquid());
        }

        // 16 Crabs
        for (int i = 0; i < 16; i++) {
            aliens.add(AlienFactory.createCrab());
        }

        // 16 Octopus
        for (int i = 0; i < 16; i++) {
            aliens.add(AlienFactory.createOctopus());
        }
    }

    private void createBunkers() {

        bunkers.clear();

        for (int i = 0; i < 4; i++) {
            bunkers.add(new Bunker());
        }
    }

    public synchronized void alienKilled(int points) {

        player.addScore(points);

        for (Alien alien : aliens) {

            if (alien.isAlive()) {
                alien.destroy();
                break;
            }
        }

        if (allAliensDead()) {
            nextRound();
        }
    }

    public synchronized void playerHit() {
        player.loseLife();
    }

    private boolean allAliensDead() {

        for (Alien alien : aliens) {

            if (alien.isAlive()) {
                return false;
            }
        }

        return true;
    }

    public synchronized void nextRoundServer() {

        speed++;

        createAliens();

        System.out.println(
            "Nueva ronda iniciada."
        );
    }

    private void nextRound() {

        speed++;

        createAliens();

        System.out.println(
            "Nueva ronda iniciada."
        );
    }

    public int generateUfoPoints() {

        Random random = new Random();

        return 500 + random.nextInt(1501);
    }

    public int getAliensAlive() {

        int count = 0;

        for (Alien alien : aliens) {

            if (alien.isAlive()) {
                count++;
            }
        }

        return count;
    }

    public int getSpeed() {
        return speed;
    }

    public int getPlayerLives() {
        return player.getLives();
    }

    public int getPlayerScore() {
        return player.getScore();
    }
}