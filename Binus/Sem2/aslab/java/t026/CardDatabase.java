import java.io.*;
import java.util.*;

public class CardDatabase {
    private Map<Integer, Card> allCards;

    public CardDatabase() {
        allCards = new HashMap<>();
        loadCards("cards.txt");
    }

    private void loadCards(String path) {
        try (BufferedReader br = new BufferedReader(new FileReader(path))) {
            String line;
            while ((line = br.readLine()) != null) {
                if (line.trim().isEmpty())
                    continue;
                String[] parts = line.split("#");
                if (parts.length < 5)
                    continue;
                String type = parts[0];
                int id = Integer.parseInt(parts[1]);
                String name = parts[2];
                String flavor = parts[3];

                if (type.equals("Monster") && parts.length >= 8) {
                    int atk = Integer.parseInt(parts[4]);
                    int lvl = Integer.parseInt(parts[5]);
                    String effectType = parts[6];
                    int effectValue = Integer.parseInt(parts[7]);
                    allCards.put(id, new MonsterCard(id, name, flavor, atk, lvl, effectType, effectValue));
                } else if (type.equals("Spell") && parts.length >= 6) {
                    String effectType = parts[4];
                    int effectValue = Integer.parseInt(parts[5]);
                    allCards.put(id, new SpellCard(id, name, flavor, effectType, effectValue));
                } else if (type.equals("Trap") && parts.length >= 6) {
                    String effectType = parts[4];
                    int effectValue = Integer.parseInt(parts[5]);
                    allCards.put(id, new TrapCard(id, name, flavor, effectType, effectValue));
                }
            }
        } catch (IOException e) {
            System.err.println("Failed to load cards.txt");
        }
    }

    public Deck getDeck(int deckId) {
        Deck deck = new Deck();
        String path = "deck" + deckId + ".txt";
        try (BufferedReader br = new BufferedReader(new FileReader(path))) {
            String line;
            while ((line = br.readLine()) != null) {
                if (line.trim().isEmpty())
                    continue;
                int cid = Integer.parseInt(line.trim());
                if (allCards.containsKey(cid)) {
                    deck.addCard(allCards.get(cid).clone());
                }
            }
        } catch (IOException | NumberFormatException e) {
            System.err.println("Failed to load " + path);
        }
        return deck;
    }
}
