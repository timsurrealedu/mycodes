public class Field {
    private MonsterCard[] monsterZone;
    private Card[] spellTrapZone;
    private SpellCard fieldSpell;

    public Field() {
        monsterZone = new MonsterCard[3];
        spellTrapZone = new Card[3];
        fieldSpell = null;
    }

    public MonsterCard[] getMonsterZone() {
        return monsterZone;
    }

    public Card[] getSpellTrapZone() {
        return spellTrapZone;
    }

    public SpellCard getFieldSpell() {
        return fieldSpell;
    }

    public void setFieldSpell(SpellCard sc) {
        this.fieldSpell = sc;
    }

    public int getAvailableMonsterZone() {
        for (int i = 0; i < 3; i++) {
            if (monsterZone[i] == null)
                return i;
        }
        return -1;
    }

    public int getAvailableSpellTrapZone() {
        for (int i = 0; i < 3; i++) {
            if (spellTrapZone[i] == null)
                return i;
        }
        return -1;
    }

    public void removeMonster(int index) {
        if (index >= 0 && index < 3)
            monsterZone[index] = null;
    }

    public void removeSpellTrap(int index) {
        if (index >= 0 && index < 3)
            spellTrapZone[index] = null;
    }
}
