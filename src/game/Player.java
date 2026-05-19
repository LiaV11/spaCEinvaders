package src.game;

public class Player {

    private int lives;
    private int score;

    public Player() {
        lives = 3;
        score = 0;
    }

    public void loseLife() {
        lives--;
    }

    public void addScore(int points) {
        score += points;
    }

    public int getLives() {
        return lives;
    }

    public int getScore() {
        return score;
    }
}