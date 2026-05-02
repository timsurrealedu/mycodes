public class SpellCard extends Card {
    private String effectType;
    private int effectValue;

    public SpellCard(int id, String name, String flavorText, String effectType, int effectValue) {
        super(id, name, flavorText, "Spell");
        this.effectType = effectType;
        this.effectValue = effectValue;
    }

    public String getEffectType() {
        return effectType;
    }

    public int getEffectValue() {
        return effectValue;
    }

    public String getSpellType() {
        if (flavorText.contains("Field Spell"))
            return "Field Spell";
        else if (flavorText.contains("Continuous Spell"))
            return "Continuous Spell";
        return "Normal Spell";
    }

    @Override
    public void printDetails() {
        System.out.println("Type: " + type);
        System.out.println("Name: " + name);
        System.out.println("Spell Type: " + getSpellType());
        System.out.println("Desc: " + flavorText);
        System.out.println("Effect: " + effectType + " (" + effectValue + ")");
    }
}
