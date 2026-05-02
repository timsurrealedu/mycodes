public class MonsterCard extends Card {
    private int attack;
    private int level;
    private String effectType;
    private int effectValue;

    public MonsterCard(int id, String name, String flavorText, int attack, int level, String effectType, int effectValue) {
        super(id, name, flavorText, "Monster");
        this.attack = attack;
        this.level = level;
        this.effectType = effectType;
        this.effectValue = effectValue;
    }

    public int getAttack() { return attack; }
    public void setAttack(int attack) { this.attack = attack >= 0 ? attack : 0; }
    public int getLevel() { return level; }
    public String getEffectType() { return effectType; }
    public int getEffectValue() { return effectValue; }

    @Override
    public void printDetails() {
        System.out.println("Type: " + type);
        System.out.println("Name: " + name);
        System.out.println("Attack: " + attack);
        System.out.println("Level: " + level);
        System.out.println("Desc: " + flavorText);
        if (!effectType.equals("NONE")) {
            System.out.println("Effect: " + effectType + " (" + effectValue + ")");
        }
        if (level > 4) {
            System.out.println("Tribute Amount: " + (level <= 6 ? 1 : 2));
        }
    }
}
