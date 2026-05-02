import java.io.*;
import java.util.*;

public class MapService {
    private char[][] grid;
    private int playerX = 0, playerY = 0;
    private int defeatedEnemies = 0;

    public class Enemy {
        public int x, y;
        public boolean defeated;
        public String deckType;

        public Enemy(int x, int y, String deckType) {
            this.x = x;
            this.y = y;
            this.defeated = false;
            this.deckType = deckType;
        }
    }

    private List<Enemy> enemies;

    public MapService(String mapPath) {
        grid = new char[10][10];
        enemies = new ArrayList<>();
        loadMap(mapPath);
        spawnEnemies();
    }

    private void loadMap(String path) {
        try (BufferedReader br = new BufferedReader(new FileReader(path))) {
            for (int i = 0; i < 10; i++) {
                String line = br.readLine();
                if (line != null && line.length() >= 10) {
                    for (int j = 0; j < 10; j++)
                        grid[i][j] = line.charAt(j);
                } else {
                    for (int j = 0; j < 10; j++)
                        grid[i][j] = '.';
                }
            }
        } catch (IOException e) {
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++)
                    grid[i][j] = '.';
            }
        }
    }

    private void spawnEnemies() {
        enemies.add(new Enemy(3, 2, "Warrior"));
        enemies.add(new Enemy(8, 3, "Dragon"));
        enemies.add(new Enemy(2, 7, "Spellcaster"));
        enemies.add(new Enemy(7, 8, "Machine"));
    }

    public void displayMap() {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (i == playerY && j == playerX) {
                    System.out.print("@ ");
                } else {
                    Enemy e = getEnemyAt(j, i);
                    if (e != null) {
                        System.out.print((e.defeated ? "X" : "!") + " ");
                    } else {
                        System.out.print(grid[i][j] + " ");
                    }
                }
            }
            System.out.println();
        }
        System.out.println("Defeated Duelists: " + defeatedEnemies);
    }

    private Enemy getEnemyAt(int x, int y) {
        for (Enemy e : enemies) {
            if (e.x == x && e.y == y)
                return e;
        }
        return null;
    }

    public Enemy getAdjacentUndefeatedEnemy() {
        for (Enemy e : enemies) {
            if (!e.defeated) {
                int dx = Math.abs(e.x - playerX);
                int dy = Math.abs(e.y - playerY);
                if ((dx == 1 && dy == 0) || (dx == 0 && dy == 1)) {
                    return e;
                }
            }
        }
        return null;
    }

    public void incrementDefeated() {
        this.defeatedEnemies++;
    }

    public int getDefeatedEnemies() {
        return defeatedEnemies;
    }

    public int getTotalEnemies() {
        return enemies.size();
    }

    public boolean movePlayer(String dir) {
        dir = dir.toUpperCase();
        int newX = playerX, newY = playerY;
        if (dir.equals("w") || dir.equals("W"))
            newY--;
        else if (dir.equals("s") || dir.equals("S"))
            newY++;
        else if (dir.equals("a") || dir.equals("A"))
            newX--;
        else if (dir.equals("d") || dir.equals("D"))
            newX++;
        else
            return false;

        if (newX >= 0 && newX < 10 && newY >= 0 && newY < 10) {
            if (getEnemyAt(newX, newY) == null) {
                playerX = newX;
                playerY = newY;
                return true;
            }
        }
        return false;
    }
}
