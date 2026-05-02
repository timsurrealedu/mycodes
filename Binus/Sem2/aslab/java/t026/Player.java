import java.util.*;

public class Player {
    private String name;
    private int lifePoints;
    private Deck deck;
    private List<Card> hand;
    private Field field;
    private boolean isAI;
    private String strategy;

    public Player(String name, Deck deck, boolean isAI, String strategy) {
        this.name = name;
        this.deck = deck;
        this.isAI = isAI;
        this.strategy = strategy;
        this.lifePoints = 4000;
        this.hand = new ArrayList<>();
        this.field = new Field();
    }

    public String getName() {
        return name;
    }

    public int getLifePoints() {
        return lifePoints;
    }

    public void setLifePoints(int lifePoints) {
        this.lifePoints = lifePoints;
    }

    public Deck getDeck() {
        return deck;
    }

    public List<Card> getHand() {
        return hand;
    }

    public Field getField() {
        return field;
    }

    public boolean isAI() {
        return isAI;
    }

    public String getStrategy() {
        return strategy;
    }

    public void reduceLifePoints(int dmg) {
        this.lifePoints -= dmg;
    }

    public void increaseLifePoints(int heal) {
        this.lifePoints += heal;
    }

    public void drawCard() {
        Card c = deck.draw();
        if (c != null) {
            hand.add(c);
        }
    }
}
