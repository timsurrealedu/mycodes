import java.io.*;
import java.util.*;

public class AuthService {
    private List<User> users;
    private String dbPath = "user.txt";

    public AuthService() {
        users = new ArrayList<>();
        loadUsers();
    }

    private void loadUsers() {
        try (BufferedReader br = new BufferedReader(new FileReader(dbPath))) {
            String line;
            while ((line = br.readLine()) != null) {
                if (line.trim().isEmpty())
                    continue;
                String[] parts = line.split("#");
                if (parts.length >= 2) {
                    users.add(new User(parts[0], parts[1]));
                }
            }
        } catch (IOException e) {
            System.err.println("Failed to load user.txt");
        }
    }

    public void saveUser(User u) {
        users.add(u);
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(dbPath, true))) {
            bw.write(u.getUsername() + "#" + u.getPasswordHash());
            bw.newLine();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public long hashDjb2(String pw) {
        long hash = 5381;
        for (int i = 0; i < pw.length(); i++) {
            hash = ((hash << 5) + hash) + pw.charAt(i);
        }
        return hash;
    }

    public boolean validateUsername(String uname) {
        if (uname.length() < 5)
            return false;
        for (User u : users) {
            if (u.getUsername().equals(uname))
                return false;
        }
        return true;
    }

    public boolean validatePassword(String pw) {
        if (pw.length() < 8)
            return false;
        boolean hasUpper = false, hasLower = false, hasDigit = false, hasSymbol = false;
        for (char c : pw.toCharArray()) {
            if (Character.isUpperCase(c))
                hasUpper = true;
            else if (Character.isLowerCase(c))
                hasLower = true;
            else if (Character.isDigit(c))
                hasDigit = true;
            else
                hasSymbol = true; // assumes any other character is symbol
        }
        return hasUpper && hasLower && hasDigit && hasSymbol;
    }

    public User login(String uname, String pw) {
        String hashed = String.valueOf(hashDjb2(pw));
        for (User u : users) {
            if (u.getUsername().equals(uname) && u.getPasswordHash().equals(hashed)) {
                return u;
            }
        }
        return null;
    }
}
