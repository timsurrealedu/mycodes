public abstract class Card implements Cloneable {
    protected int id;
    protected String name;
    protected String flavorText;
    protected String type; 

    public Card(int id, String name, String flavorText, String type) {
        this.id = id;
        this.name = name;
        this.flavorText = flavorText;
        this.type = type;
    }

    public int getId() { return id; }
    public String getName() { return name; }
    public String getFlavorText() { return flavorText; }
    public String getType() { return type; }

    public abstract void printDetails();

    @Override
    public Card clone() {
        try {
            return (Card) super.clone();
        } catch(CloneNotSupportedException e) {
            return null;
        }
    }
}
