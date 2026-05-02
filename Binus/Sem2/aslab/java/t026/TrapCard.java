public class TrapCard extends Card {
    private String effectType;
    private int effectValue;
    public boolean justSet;

    public TrapCard(int id, String name, String flavorText, String effectType, int effectValue) {
        super(id, name, flavorText, "Trap");
        this.effectType = effectType;
        this.effectValue = effectValue;
        this.justSet = false;
    }

    public String getEffectType() {
        return effectType;
    }

    public int getEffectValue() {
        return effectValue;
    }

    @Override
    public void printDetails() {
        System.out.println("Type: " + type);
        System.out.println("Name: " + name);
        System.out.println("Desc: " + flavorText);
        System.out.println("Effect: " + effectType + " (" + effectValue + ")");
    }
}
