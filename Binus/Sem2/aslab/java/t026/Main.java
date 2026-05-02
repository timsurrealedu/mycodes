import java.util.*;

public class Main {
    private static Scanner scanner = new Scanner(System.in);
    private static AuthService authService = new AuthService();
    private static User currentUser = null;
    private static CardDatabase cardDb = new CardDatabase();
    private static Player player = null;

    public static void main(String[] args) {
        landingPage();
    }

    private static void landingPage() {
        while (true) {
            System.out.println("====== Landing Page ======");
            System.out.println("1. Login");
            System.out.println("2. Register");
            System.out.println("3. Exit");
            System.out.print(">> ");
            String choice = scanner.nextLine();
            if (choice.equals("1")) {
                login();
                if (currentUser != null)
                    homePage();
            } else if (choice.equals("2")) {
                register();
            } else if (choice.equals("3")) {
                System.out.println("Exiting...");
                System.exit(0);
            } else {
                System.out.println("Invalid choice. Input must be between 1 and 3 inclusively.");
            }
        }
    }

    private static void login() {
        System.out.print("Username: ");
        String uname = scanner.nextLine();
        System.out.print("Password: ");
        String pwd = scanner.nextLine();
        User u = authService.login(uname, pwd);
        if (u != null) {
            currentUser = u;
        } else {
            System.out.println("Invalid credentials.");
        }
    }

    private static void register() {
        System.out.print("Username: ");
        String uname = scanner.nextLine();
        if (!authService.validateUsername(uname)) {
            System.out.println("Invalid username.");
            return;
        }
        System.out.print("Password: ");
        String pwd = scanner.nextLine();
        if (!authService.validatePassword(pwd)) {
            System.out.println("Invalid password.");
            return;
        }
        User u = new User(uname, String.valueOf(authService.hashDjb2(pwd)));
        authService.saveUser(u);
        System.out.println("Registration successful.");
    }

    private static void homePage() {
        while (currentUser != null) {
            System.out.println("====== Home Page ======");
            System.out.println("Welcome, " + currentUser.getUsername());
            System.out.println("1. Explore Map");
            System.out.println("2. How to Play");
            System.out.println("3. Exit");
            System.out.print(">> ");
            String choice = scanner.nextLine();
            if (choice.equals("1")) {
                deckSelectionPage();
            } else if (choice.equals("2")) {
                howToPlayPage();
            } else if (choice.equals("3")) {
                System.out.println("Exiting...");
                System.exit(0);
            } else {
                System.out.println("Invalid choice. Must be 1-3 inclusively.");
            }
        }
    }

    private static void deckSelectionPage() {
        System.out.println("====== Deck Selection ======");
        System.out.println("1. Warrior Deck");
        System.out.println("2. Dragon Deck");
        System.out.println("3. Spellcaster Deck");
        System.out.println("4. Machine Deck");
        System.out.print("Choose a deck (1-4): ");
        String choice = scanner.nextLine();
        int deckId;
        try {
            deckId = Integer.parseInt(choice);
            if (deckId >= 1 && deckId <= 4) {
                Deck deck = cardDb.getDeck(deckId);
                player = new Player(currentUser.getUsername(), deck, false, "Player");
                player.getDeck().shuffle();
                for (int i = 0; i < 5; i++)
                    player.drawCard();
                System.out.println("Deck selected! Proceed to game.");
                gamePage();
                return;
            }
        } catch (NumberFormatException e) {
        }
        System.out.println("Invalid input. Returning to home page.");
    }

    private static void howToPlayPage() {
        int page = 1;
        while (true) {
            System.out.println("--- How To Play (Page " + page + "/5) ---");
            if (page == 1)
                System.out.println("1. Walk around map using W A S D.");
            else if (page == 2)
                System.out.println("2. Yu-Gi-Oh consists of Monsters, Spells, Traps.");
            else if (page == 3)
                System.out.println("3. Use attacks and effects to reduce enemy LP.");
            else if (page == 4)
                System.out.println("4. Max 3 monsters on field.");
            else if (page == 5)
                System.out.println("5. Win by reducing enemy LP to 0.");
            System.out.print("Press A to go left, D to go right, Q to quit: ");
            String act = scanner.nextLine().toUpperCase();
            if (act.equals("A")) {
                page = (page == 1) ? 5 : page - 1;
            } else if (act.equals("D")) {
                page = (page == 5) ? 1 : page + 1;
            } else if (act.equals("Q")) {
                return;
            } else {
                System.out.println("Invalid input.");
            }
        }
    }

    private static void gamePage() {
        MapService mapService = new MapService("map.txt");
        while (true) {
            mapService.displayMap();
            if (mapService.getDefeatedEnemies() == mapService.getTotalEnemies()) {
                System.out.println("You defeated all 4 enemies!");
                return;
            }
            MapService.Enemy adjacent = mapService.getAdjacentUndefeatedEnemy();
            if (adjacent != null) {
                System.out.print("Duel the NPC? (Y/N): ");
                String d = scanner.nextLine().toUpperCase();
                if (d.equals("Y")) {
                    Deck enemyDeck;
                    if (adjacent.deckType.equals("Warrior"))
                        enemyDeck = cardDb.getDeck(1);
                    else if (adjacent.deckType.equals("Dragon"))
                        enemyDeck = cardDb.getDeck(2);
                    else if (adjacent.deckType.equals("Spellcaster"))
                        enemyDeck = cardDb.getDeck(3);
                    else
                        enemyDeck = cardDb.getDeck(4);

                    Player enemy = new Player("Enemy_" + adjacent.deckType, enemyDeck, true, adjacent.deckType);
                    enemy.getDeck().shuffle();
                    for (int i = 0; i < 5; i++)
                        enemy.drawCard();

                    DuelService ds = new DuelService(player, enemy, scanner);
                    boolean win = ds.startDuel();
                    if (win) {
                        System.out.println("You won the duel!");
                        adjacent.defeated = true;
                        mapService.incrementDefeated();
                        // refresh player lp and deck
                        player.setLifePoints(4000);
                    } else {
                        System.out.println("You lost the duel. Game Over.");
                        System.exit(0);
                    }
                }
            }
            System.out.print("Move (W/A/S/D): ");
            String move = scanner.nextLine();
            mapService.movePlayer(move);
        }
    }
}
