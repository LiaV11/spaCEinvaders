package src.game;

public class Alien {

    private int points;
    private boolean alive;

    public Alien(int points) {
        this.points = points;
        this.alive = true;
    }

    public void destroy() {
        alive = false;
    }

    public int getPoints() {
        return points;
    }

    public boolean isAlive() {
        return alive;
    }
}