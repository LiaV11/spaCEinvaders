package src.patterns;

import src.game.Alien;

public class AlienFactory {

    public static Alien createSquid() {
        return new Alien(10);
    }

    public static Alien createCrab() {
        return new Alien(20);
    }

    public static Alien createOctopus() {
        return new Alien(40);
    }
}