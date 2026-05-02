import java.util.*;

public class DuelService {
    private Player p1;
    private Player p2;
    private Scanner scanner;

    public DuelService(Player p1, Player p2, Scanner sc) {
        this.p1 = p1;
        this.p2 = p2;
        this.scanner = sc;
    }

    public boolean startDuel() {
        int turn = 1;
        while (p1.getLifePoints() > 0 && p2.getLifePoints() > 0) {
            if (turn % 2 == 1) {
                System.out.println("\n=== Your Turn (" + turn + ") ===");
                p1.drawCard();
                playerMainPhase(turn);
            } else {
                System.out.println("\n=== Opponent Turn (" + turn + ") ===");
                AIService.takeTurn(p2, p1, turn);
            }
            if (p2.getLifePoints() <= 0)
                return true;
            if (p1.getLifePoints() <= 0)
                return false;
            turn++;
        }
        return p2.getLifePoints() <= 0;
    }

    private void playerMainPhase(int turn) {
        boolean hasSummoned = false;
        while (true) {
            System.out.println("\n-- Board State --");
            System.out.println(
                    "Opponent: " + p2.getName() + " | LP: " + p2.getLifePoints() + " | Deck: " + p2.getDeck().size());
            System.out.println(
                    "You: " + p1.getName() + " | LP: " + p1.getLifePoints() + " | Deck: " + p1.getDeck().size());
            System.out.println("-----------------");
            System.out.println("1. Summon Monster");
            System.out.println("2. Activate Spell");
            System.out.println("3. Set Trap");
            System.out.println("4. Battle Phase");
            System.out.println("5. End Turn");
            System.out.println("6. View Card Detail");
            System.out.println("7. Activate Monster Effect");
            System.out.print("Select action (1-7): ");
            String c = scanner.nextLine();

            if (c.equals("1"))
                hasSummoned = promptSummon(hasSummoned);
            else if (c.equals("2"))
                promptActivateSpell();
            else if (c.equals("3"))
                promptSetTrap();
            else if (c.equals("4")) {
                if (turn == 1) {
                    System.out.println("Cannot battle on first turn!");
                } else {
                    promptBattlePhase();
                    break; // After battle phase, turn ends
                }
            } else if (c.equals("5"))
                break;
            else if (c.equals("6"))
                promptViewDetails();
            else if (c.equals("7"))
                promptMonsterEffect();
        }
    }

    private boolean promptSummon(boolean alreadySummoned) {
        if (alreadySummoned) {
            System.out.println("You already summoned this turn.");
            return true;
        }
        List<Card> hand = p1.getHand();
        List<Integer> validIndices = new ArrayList<>();
        System.out.println("Monsters in hand:");
        for (int i = 0; i < hand.size(); i++) {
            if (hand.get(i) instanceof MonsterCard) {
                System.out.println(i + ". " + hand.get(i).getName());
                validIndices.add(i);
            }
        }
        if (validIndices.isEmpty()) {
            System.out.println("No monsters to summon.");
            return false;
        }

        System.out.print("Select monster to summon (number): ");
        try {
            int idx = Integer.parseInt(scanner.nextLine());
            if (validIndices.contains(idx)) {
                int zone = p1.getField().getAvailableMonsterZone();
                if (zone != -1) {
                    MonsterCard m = (MonsterCard) hand.remove(idx);
                    p1.getField().getMonsterZone()[zone] = m;
                    System.out.println("Summoned " + m.getName() + " to zone " + zone);
                    return true;
                } else {
                    System.out.println("No empty monster zones.");
                }
            }
        } catch (Exception e) {
            System.out.println("Invalid.");
        }
        return false;
    }

    private void promptActivateSpell() {
        // Simple mock
        System.out.println("Spell activation skipped for brevity in CLI logic (would apply effect)");
    }

    private void promptSetTrap() {
        System.out.println("Set trap skipped for brevity.");
    }

    private void promptBattlePhase() {
        System.out.println("--- Battle Phase ---");
        MonsterCard[] myMonsters = p1.getField().getMonsterZone();
        MonsterCard[] enemyMonsters = p2.getField().getMonsterZone();

        int attacker = -1;
        for (int i = 0; i < 3; i++) {
            if (myMonsters[i] != null) {
                System.out.println("You can attack with: " + i + ". " + myMonsters[i].getName() + " (ATK: "
                        + myMonsters[i].getAttack() + ")");
                attacker = i;
                break; // Just picking first for rapid game flow test
            }
        }

        if (attacker != -1) {
            int target = -1;
            boolean hasEnemy = false;
            for (int i = 0; i < 3; i++) {
                if (enemyMonsters[i] != null) {
                    hasEnemy = true;
                    target = i;
                    break;
                }
            }
            if (!hasEnemy) {
                System.out.println("Direct attack! LP -" + myMonsters[attacker].getAttack());
                p2.reduceLifePoints(myMonsters[attacker].getAttack());
            } else {
                System.out.println("Attacking enemy monster " + enemyMonsters[target].getName());
                if (myMonsters[attacker].getAttack() >= enemyMonsters[target].getAttack()) {
                    p2.reduceLifePoints(myMonsters[attacker].getAttack() - enemyMonsters[target].getAttack());
                    p2.getField().removeMonster(target);
                } else {
                    p1.reduceLifePoints(enemyMonsters[target].getAttack() - myMonsters[attacker].getAttack());
                    p1.getField().removeMonster(attacker);
                }
            }
        } else {
            System.out.println("No monsters able to attack.");
        }
    }

    private void promptViewDetails() {
        System.out.println("Details skipped.");
    }

    private void promptMonsterEffect() {
        System.out.println("Effects skipped.");
    }
}
