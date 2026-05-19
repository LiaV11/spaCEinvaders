package src.game;

public class Bunker {

    private int health;

    public Bunker() {
        health = 100;
    }

    public void damage(int amount) {
        health -= amount;

        if (health < 0)
            health = 0;
    }

    public int getHealth() {
        return health;
    }
}