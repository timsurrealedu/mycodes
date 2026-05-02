public class AIService {
    public static void takeTurn(Player ai, Player player, int turnNumber) {
        System.out.println(">> " + ai.getName() + " starts turn.");
        ai.drawCard();

        // Very basic generic AI for all strategies to satisfy assignment simply.
        // Summons the first summonable monster.
        for (int i = 0; i < ai.getHand().size(); i++) {
            Card c = ai.getHand().get(i);
            if (c instanceof MonsterCard) {
                MonsterCard m = (MonsterCard) c;
                if (m.getLevel() <= 4) { // only simple normal summon
                    int availableZone = ai.getField().getAvailableMonsterZone();
                    if (availableZone != -1) {
                        ai.getField().getMonsterZone()[availableZone] = m;
                        ai.getHand().remove(i);
                        System.out.println(">> " + ai.getName() + " summons " + m.getName() + ".");
                        break;
                    }
                }
            }
        }

        // Activates the first spell
        for (int i = 0; i < ai.getHand().size(); i++) {
            Card c = ai.getHand().get(i);
            if (c instanceof SpellCard) {
                SpellCard sc = (SpellCard) c;
                int zone = ai.getField().getAvailableSpellTrapZone();
                if (zone != -1 && sc.getSpellType().equals("Normal Spell")) {
                    System.out.println(">> " + ai.getName() + " activates " + sc.getName() + ".");
                    // Basic eff logic skipped for brevity, just deduct health if burn.
                    if (sc.getEffectType().equals("BURN_DAMAGE")) {
                        player.reduceLifePoints(sc.getEffectValue());
                    }
                    ai.getHand().remove(i);
                    break;
                }
            }
        }

        // Battle
        if (turnNumber > 1) {
            MonsterCard[] monsters = ai.getField().getMonsterZone();
            for (MonsterCard m : monsters) {
                if (m != null) {
                    // find a target
                    MonsterCard[] playerMonsters = player.getField().getMonsterZone();
                    int targetIndex = -1;
                    for (int j = 0; j < 3; j++) {
                        if (playerMonsters[j] != null) {
                            targetIndex = j;
                            break;
                        }
                    }

                    if (targetIndex != -1) {
                        MonsterCard target = playerMonsters[targetIndex];
                        System.out.println(
                                ">> " + ai.getName() + "'s " + m.getName() + " attacks " + target.getName() + ".");
                        if (m.getAttack() >= target.getAttack()) {
                            player.reduceLifePoints(m.getAttack() - target.getAttack());
                            player.getField().removeMonster(targetIndex);
                        } else {
                            ai.reduceLifePoints(target.getAttack() - m.getAttack());
                        }
                    } else {
                        System.out.println(">> " + ai.getName() + "'s " + m.getName() + " attacks directly!");
                        player.reduceLifePoints(m.getAttack());
                    }
                }
            }
        }

        System.out.println(">> " + ai.getName() + " ends their turn.");
    }
}
