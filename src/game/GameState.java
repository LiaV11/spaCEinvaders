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

        aliens.add(
                AlienFactory.createSquid());

        aliens.add(
                AlienFactory.createCrab());

        aliens.add(
                AlienFactory.createOctopus());
    }

    private void createBunkers() {

        bunkers.clear();

        for (int i = 0; i < 4; i++) {
            bunkers.add(new Bunker());
        }
    }

    public void alienKilled() {

        player.addScore(10);

        if (allAliensDead()) {
            nextRound();
        }
    }

    public void playerHit() {
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

    private void nextRound() {
        speed++;
        createAliens();

        System.out.println(
                "Nueva ronda iniciada.");
    }

    public int generateUfoPoints() {
        Random random = new Random();

        return 500 +
                random.nextInt(1001);
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