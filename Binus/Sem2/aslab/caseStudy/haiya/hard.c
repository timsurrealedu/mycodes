#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#include <conio.h>

void initTerm() {}
void resetTerm() {}
void clearScreen() { system("cls"); }
void sleepMs(int ms) { Sleep(ms); }
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}
int checkKey() {
    if (_kbhit()) {
        int k = _getch();
        if (k == 0 || k == 224) {
            k = _getch();
            if (k == 72) return 1000;
            if (k == 80) return 1001;
            if (k == 75) return 1002;
            if (k == 77) return 1003;
        }
        if (k == 13) return 13;
        if (k == 32) return 32;
        return k;
    }
    return 0;
}
int waitKey() {
    int k = _getch();
    if (k == 0 || k == 224) {
        k = _getch();
        if (k == 72) return 1000;
        if (k == 80) return 1001;
        if (k == 75) return 1002;
        if (k == 77) return 1003;
    }
    if (k == 13) return 13;
    return k;
}

#else

#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/select.h>

struct termios orig_termios;

void resetTerm() {
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
    printf("\033[?25h");
    fflush(stdout);
}
void initTerm() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}
void clearScreen() {
    printf("\033[2J\033[H");
    fflush(stdout);
}
void sleepMs(int ms) { usleep(ms * 1000); }
void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y + 1, x + 1);
}
void hideCursor() {
    printf("\033[?25l");
    fflush(stdout);
}

int _kbhit() {
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv) > 0;
}

int _getch() {
    char ch = 0;
    if (read(0, &ch, 1) < 0) return 0;
    return ch;
}

int checkKey() {
    if (_kbhit()) {
        int k = _getch();
        if (k == 27) {
            if (_kbhit()) {
                k = _getch();
                if (k == '[') {
                    k = _getch();
                    if (k == 'A') return 1000;
                    if (k == 'B') return 1001;
                    if (k == 'D') return 1002;
                    if (k == 'C') return 1003;
                }
            }
            return 27;
        }
        if (k == 10) return 13;
        if (k == 32) return 32;
        return k;
    }
    return 0;
}

int waitKey() {
    int k = _getch();
    if (k == 27) {
        usleep(1000);
        if (_kbhit()) {
            k = _getch();
            if (k == '[') {
                k = _getch();
                if (k == 'A') return 1000;
                if (k == 'B') return 1001;
                if (k == 'D') return 1002;
                if (k == 'C') return 1003;
            }
        }
        return 27;
    }
    if (k == 10) return 13;
    return k;
}
#endif

#define TABLE_SIZE 100
#define GAME_WIDTH 60
#define GAME_HEIGHT 30
#define NUM_SHIELDS 3
#define BLOCKS_PER_SHIELD 12

typedef struct User {
    char username[50];
    char password[50];
    int score;
    struct User* next;
} User;

typedef struct EnemyType {
    char type[20];
    char symbol[10];
    int scoreValue;
} EnemyType;

typedef struct Enemy {
    int x, y;
    int typeIndex;
    struct Enemy* prev;
    struct Enemy* next;
} Enemy;

typedef struct Bullet {
    float x, y;
    float speed;
    int isPlayer;
    struct Bullet* next;
} Bullet;

typedef struct ShieldBlock {
    int x, y;
    int active;
} ShieldBlock;

User* hashTable[TABLE_SIZE];
EnemyType enemyTypes[10];
int enemyTypeCount = 0;

Enemy* activeEnemiesHead = NULL;
Enemy* activeEnemiesTail = NULL;
Bullet* bulletsHead = NULL;
ShieldBlock shields[NUM_SHIELDS * BLOCKS_PER_SHIELD];

User* currentUser = NULL;
int currentScore = 0;
int currentLives = 3;

void decrypt(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = (str[i] - 'A' - 3 + 26) % 26 + 'A';
        } else if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = (str[i] - 'a' - 3 + 26) % 26 + 'a';
        } else if (str[i] >= '0' && str[i] <= '9') {
            str[i] = (str[i] - '0' - 3 + 10) % 10 + '0';
        }
    }
}

void encrypt(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = (str[i] - 'A' + 3) % 26 + 'A';
        } else if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = (str[i] - 'a' + 3) % 26 + 'a';
        } else if (str[i] >= '0' && str[i] <= '9') {
            str[i] = (str[i] - '0' + 3) % 10 + '0';
        }
    }
}

unsigned int hash(char* str) {
    unsigned int hashValue = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        hashValue = hashValue * 31 + str[i];
    }
    return hashValue % TABLE_SIZE;
}

void insertUser(char* username, char* password, int score) {
    unsigned int index = hash(username);
    User* newUser = (User*)malloc(sizeof(User));
    strcpy(newUser->username, username);
    strcpy(newUser->password, password);
    newUser->score = score;
    newUser->next = hashTable[index];
    hashTable[index] = newUser;
}

User* findUser(char* username) {
    unsigned int index = hash(username);
    User* current = hashTable[index];
    while (current != NULL) {
        if (strcmp(current->username, username) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void loadUsers() {
    FILE* file = fopen("user.txt", "r");
    if (!file) return;
    char line[150];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        char* username = strtok(line, "#");
        char* password = strtok(NULL, "#");
        if (username && password) {
            insertUser(username, password, 0);
        }
    }
    fclose(file);
}

void loadScores() {
    FILE* file = fopen("scores.txt", "r");
    if (!file) return;
    char line[150];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        char* encName = strtok(line, "=");
        char* encScore = strtok(NULL, "=");
        if (encName && encScore) {
            decrypt(encName);
            decrypt(encScore);
            int score = atoi(encScore);
            User* u = findUser(encName);
            if (u) {
                u->score = score;
            }
        }
    }
    fclose(file);
}

void loadEnemyTypes() {
    FILE* file = fopen("enemyTypes.txt", "r");
    if (!file) return;
    char line[100];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        char* type = strtok(line, ";");
        char* symbol = strtok(NULL, ";");
        char* valStr = strtok(NULL, ";");
        if (type && symbol && valStr) {
            strcpy(enemyTypes[enemyTypeCount].type, type);
            strcpy(enemyTypes[enemyTypeCount].symbol, symbol);
            enemyTypes[enemyTypeCount].scoreValue = atoi(valStr);
            enemyTypeCount++;
        }
    }
    fclose(file);
}

void saveUsersAndScores() {
    FILE* uf = fopen("user.txt", "w");
    FILE* sf = fopen("scores.txt", "w");
    for (int i = 0; i < TABLE_SIZE; i++) {
        User* curr = hashTable[i];
        while (curr) {
            fprintf(uf, "%s#%s\n", curr->username, curr->password);
            char eName[50], eScore[20];
            strcpy(eName, curr->username);
            sprintf(eScore, "%d", curr->score);
            encrypt(eName);
            encrypt(eScore);
            fprintf(sf, "%s=%s\n", eName, eScore);
            curr = curr->next;
        }
    }
    fclose(uf);
    fclose(sf);
}

void addEnemy(int x, int y, int typeIndex) {
    Enemy* newEnemy = (Enemy*)malloc(sizeof(Enemy));
    newEnemy->x = x;
    newEnemy->y = y;
    newEnemy->typeIndex = typeIndex;
    newEnemy->next = NULL;
    newEnemy->prev = activeEnemiesTail;
    if (activeEnemiesTail) activeEnemiesTail->next = newEnemy;
    else activeEnemiesHead = newEnemy;
    activeEnemiesTail = newEnemy;
}

void removeEnemy(Enemy* e) {
    if (e->prev) e->prev->next = e->next;
    else activeEnemiesHead = e->next;
    if (e->next) e->next->prev = e->prev;
    else activeEnemiesTail = e->prev;
    free(e);
}

void addBullet(float x, float y, float speed, int isPlayer) {
    Bullet* newBullet = (Bullet*)malloc(sizeof(Bullet));
    newBullet->x = x;
    newBullet->y = y;
    newBullet->speed = speed;
    newBullet->isPlayer = isPlayer;
    newBullet->next = bulletsHead;
    bulletsHead = newBullet;
}

void removeBullet(Bullet* prev, Bullet* curr) {
    if (prev) prev->next = curr->next;
    else bulletsHead = curr->next;
    free(curr);
}

void initShields() {
    int shieldSpacing = GAME_WIDTH / (NUM_SHIELDS + 1);
    int startY = GAME_HEIGHT - 6;
    int idx = 0;
    for (int s = 0; s < NUM_SHIELDS; s++) {
        int startX = shieldSpacing * (s + 1) - 2;
        for (int dy = 0; dy < 3; dy++) {
            for (int dx = 0; dx < 5; dx++) {
                if (dy == 0 && (dx == 0 || dx == 4)) continue;
                if (dy == 2 && (dx == 1 || dx == 2 || dx == 3)) continue;
                shields[idx].x = startX + dx;
                shields[idx].y = startY + dy;
                shields[idx].active = 1;
                idx++;
            }
        }
    }
}

void drawBorders() {
    clearScreen();
    for(int i = 0; i < GAME_WIDTH; i++) {
        gotoxy(i, 0); printf("-");
        gotoxy(i, GAME_HEIGHT); printf("-");
    }
    for(int i = 0; i <= GAME_HEIGHT; i++) {
        gotoxy(0, i); printf("|");
        gotoxy(GAME_WIDTH, i); printf("|");
    }
    fflush(stdout);
}

void displayLandingPage() {
    clearScreen();
    gotoxy(20, 10);
    printf("HoloKron");
    gotoxy(15, 15);
    printf("Press any key to continue...");
    fflush(stdout);
    waitKey();
}

void spawnWave(int* baseSpeedMultiplier) {
    while (activeEnemiesHead) removeEnemy(activeEnemiesHead);
    for(int i=0; i<3; i++) {
        for(int j=0; j<8; j++) {
            addEnemy(10 + j*5, 3 + i*2, i % enemyTypeCount);
        }
    }
    (*baseSpeedMultiplier)++;
}

void playGame() {
    if (enemyTypeCount == 0) {
        clearScreen();
        gotoxy(10, 10); printf("ERROR: enemyTypes.txt is missing or empty!");
        gotoxy(10, 12); printf("Press any key to return.");
        fflush(stdout);
        waitKey();
        return;
    }

    srand(time(NULL));
    int playerX = GAME_WIDTH / 2;
    int playerY = GAME_HEIGHT - 2;
    currentScore = 0;
    currentLives = 3;
    bool running = true;
    
    int enemyDir = 1;
    bool dropDown = false;
    int waveSpeedMultiplier = 0;
    int framesSinceLastShot = 0;
    
    while (bulletsHead) removeBullet(NULL, bulletsHead);
    spawnWave(&waveSpeedMultiplier);
    initShields();
    drawBorders();

    for (int i = 0; i < NUM_SHIELDS * BLOCKS_PER_SHIELD; i++) {
        if (shields[i].active) {
            gotoxy(shields[i].x, shields[i].y);
            printf("#");
        }
    }

    int ufoActive = 0;
    int ufoX = 0;

    while (running && currentLives > 0) {
        if (!activeEnemiesHead) {
            spawnWave(&waveSpeedMultiplier);
        }

        int key = checkKey();
        if (key != 0) {
            if (key == 1002 && playerX > 2) playerX--;
            if (key == 1003 && playerX < GAME_WIDTH - 4) playerX++;
            if (key == 32) {
                bool canShoot = true;
                Bullet* b = bulletsHead;
                while(b) {
                    if (b->isPlayer) canShoot = false;
                    b = b->next;
                }
                if (canShoot) {
                    addBullet(playerX + 1, playerY - 1, -1.0f, 1);
                }
            }
            if (key == 27) {
                running = false;
            }
        }

        if (!ufoActive && (rand() % 100 < 1)) {
            ufoActive = 1;
            ufoX = 1;
        }

        if (ufoActive) {
            gotoxy(ufoX, 1); printf("   ");
            ufoX++;
            if (ufoX >= GAME_WIDTH - 4) {
                ufoActive = 0;
            } else {
                gotoxy(ufoX, 1); printf("<U>");
            }
        }

        int enemyBulletsCount = 0;
        Bullet* countB = bulletsHead;
        while(countB) {
            if (!countB->isPlayer) enemyBulletsCount++;
            countB = countB->next;
        }

        framesSinceLastShot++;
        int chanceToShoot = 6 - enemyBulletsCount;
        if (chanceToShoot < 2) chanceToShoot = 2;

        if (framesSinceLastShot >= 35 || (rand() % 100 < chanceToShoot)) {
            int bottomEnemies[GAME_WIDTH] = {0};
            int activeCols[GAME_WIDTH] = {0};
            int numActiveCols = 0;

            Enemy* currE = activeEnemiesHead;
            while(currE) {
                if (currE->y > bottomEnemies[currE->x]) {
                    if (bottomEnemies[currE->x] == 0) {
                        activeCols[numActiveCols++] = currE->x;
                    }
                    bottomEnemies[currE->x] = currE->y;
                }
                currE = currE->next;
            }

            if (numActiveCols > 0) {
                int randomColIdx = rand() % numActiveCols;
                int shootX = activeCols[randomColIdx];
                int shootY = bottomEnemies[shootX];
                
                float speeds[] = {1.0f, 1.3f, 1.6f};
                float s = speeds[rand() % 3];
                
                addBullet(shootX + 1, (float)shootY + 1.0f, s, 0);
                framesSinceLastShot = 0;
            }
        }

        Bullet* prevB = NULL;
        Bullet* currB = bulletsHead;
        while (currB) {
            gotoxy((int)currB->x, (int)currB->y);
            printf(" ");
            
            float nextY = currB->y + currB->speed;
            bool destroyed = false;
            int bX = (int)currB->x;
            int bY = (int)nextY;

            if (bY <= 1 || bY >= GAME_HEIGHT - 1) {
                destroyed = true;
            }

            if (!destroyed) {
                for (int i = 0; i < NUM_SHIELDS * BLOCKS_PER_SHIELD; i++) {
                    if (shields[i].active && bX >= shields[i].x && bX <= shields[i].x && bY == shields[i].y) {
                        shields[i].active = 0;
                        gotoxy(shields[i].x, shields[i].y);
                        printf(" ");
                        destroyed = true;
                        break;
                    }
                }
            }

            if (!destroyed && currB->isPlayer) {
                Enemy* currE = activeEnemiesHead;
                while (currE) {
                    if (bX >= currE->x && bX <= currE->x + 2 && bY == currE->y) {
                        currentScore += enemyTypes[currE->typeIndex].scoreValue;
                        gotoxy(currE->x, currE->y); printf("   ");
                        Enemy* toDelete = currE;
                        currE = currE->next;
                        removeEnemy(toDelete);
                        destroyed = true;
                        break;
                    } else {
                        currE = currE->next;
                    }
                }

                if (!destroyed && ufoActive && bX >= ufoX && bX <= ufoX + 2 && bY == 1) {
                    int ufoScores[] = {50, 100, 150, 200, 300};
                    currentScore += ufoScores[rand() % 5];
                    gotoxy(ufoX, 1); printf("   ");
                    ufoActive = 0;
                    destroyed = true;
                }
            } else if (!destroyed && !currB->isPlayer) {
                if (bX >= playerX && bX <= playerX + 2 && bY == playerY) {
                    currentLives--;
                    destroyed = true;
                }
            }

            if (destroyed) {
                Bullet* toDelete = currB;
                currB = currB->next;
                removeBullet(prevB, toDelete);
            } else {
                currB->y = nextY;
                gotoxy((int)currB->x, (int)currB->y);
                printf(currB->isPlayer ? "|" : "v");
                prevB = currB;
                currB = currB->next;
            }
        }

        static int frameCount = 0;
        frameCount++;
        if (frameCount % 10 == 0) {
            dropDown = false;
            Enemy* e = activeEnemiesHead;
            while (e) {
                gotoxy(e->x, e->y); printf("   ");
                if (e->x + enemyDir <= 1 || e->x + enemyDir >= GAME_WIDTH - 4) {
                    dropDown = true;
                }
                e = e->next;
            }

            if (dropDown) enemyDir *= -1;

            e = activeEnemiesHead;
            while (e) {
                if (dropDown) e->y++;
                else e->x += enemyDir;
                gotoxy(e->x, e->y);
                printf("%s", enemyTypes[e->typeIndex].symbol);
                e = e->next;
            }
        }

        gotoxy(playerX - 1, playerY); printf("     ");
        gotoxy(playerX, playerY); printf("<A>");

        gotoxy(GAME_WIDTH + 5, 5); printf("SCORE: %d   ", currentScore);
        gotoxy(GAME_WIDTH + 5, 8); printf("LIVES: %d   ", currentLives);
        gotoxy(GAME_WIDTH + 5, 11); printf("HIGH SCORE: %d   ", currentUser ? currentUser->score : 0);

        fflush(stdout);
        sleepMs(30);
    }

    if (currentUser && currentScore > currentUser->score) {
        currentUser->score = currentScore;
        saveUsersAndScores();
    }

    clearScreen();
    gotoxy(20, 10);
    printf("GAME OVER");
    gotoxy(20, 12);
    printf("Score: %d", currentScore);
    fflush(stdout);
    waitKey();
}

void bubbleSortScores(User** arr, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (arr[j]->score < arr[j + 1]->score) {
                User* temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void showLeaderboard() {
    User* arr[TABLE_SIZE * 10];
    int count = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        User* curr = hashTable[i];
        while (curr) {
            arr[count++] = curr;
            curr = curr->next;
        }
    }

    bubbleSortScores(arr, count);

    int page = 0;
    int maxPage = (count - 1) / 10;
    if (maxPage < 0) maxPage = 0;

    while (true) {
        clearScreen();
        gotoxy(10, 2);
        printf("LEADERBOARD");
        gotoxy(5, 4);
        printf("Rank\tUsername\t\tScore");
        
        int start = page * 10;
        int end = start + 10;
        if (end > count) end = count;

        for (int i = start; i < end; i++) {
            gotoxy(5, 6 + (i - start));
            printf("%d\t%s\t\t%d", i + 1, arr[i]->username, arr[i]->score);
        }

        gotoxy(5, 18);
        printf("Page %d/%d", page + 1, maxPage + 1);
        gotoxy(5, 20);
        printf("Use LEFT/RIGHT to navigate, ESC to return.");
        fflush(stdout);

        int key = waitKey();
        if (key == 27) break;
        if (key == 1002 && page > 0) page--;
        if (key == 1003 && page < maxPage) page++;
    }
}

void showHowToPlay() {
    clearScreen();
    gotoxy(10, 2); printf("Instructions:");
    gotoxy(10, 4); printf("1. Use arrow keys to navigate the menu.");
    gotoxy(10, 5); printf("2. Press Enter to select an option.");
    gotoxy(10, 6); printf("3. In the game, use arrow left and right to move.");
    gotoxy(10, 7); printf("4. Press spacebar to shoot bullets at enemies.");
    gotoxy(10, 8); printf("5. Defeat enemies and earn points.");
    gotoxy(10, 10); printf("Press ESC to go back...");
    fflush(stdout);
    while (waitKey() != 27);
}

void handleRegister() {
    clearScreen();
    char user[50], pass[50];
    gotoxy(10, 5); printf("Register New Account");
    gotoxy(10, 7); printf("Username: ");
    fflush(stdout);
    resetTerm();
    if (scanf("%s", user) != 1) return;
    initTerm();
    
    if (findUser(user)) {
        gotoxy(10, 9); printf("Username already exists!");
        fflush(stdout);
        waitKey();
        return;
    }
    gotoxy(10, 8); printf("Password: ");
    fflush(stdout);
    resetTerm();
    if (scanf("%s", pass) != 1) return;
    initTerm();
    
    encrypt(pass);
    insertUser(user, pass, 0);
    saveUsersAndScores();
    gotoxy(10, 10); printf("Registration successful!");
    fflush(stdout);
    waitKey();
}

void handleLogin() {
    clearScreen();
    char user[50], pass[50], encPass[50];
    gotoxy(10, 5); printf("Login");
    gotoxy(10, 7); printf("Username: ");
    fflush(stdout);
    resetTerm();
    if (scanf("%s", user) != 1) return;
    initTerm();
    
    gotoxy(10, 8); printf("Password: ");
    fflush(stdout);
    resetTerm();
    if (scanf("%s", pass) != 1) return;
    initTerm();
    
    strcpy(encPass, pass);
    encrypt(encPass);

    User* u = findUser(user);
    if (u && strcmp(u->password, encPass) == 0) {
        currentUser = u;
        gotoxy(10, 10); printf("Login successful!");
    } else {
        gotoxy(10, 10); printf("Invalid credentials!");
    }
    fflush(stdout);
    waitKey();
}

int main() {
    atexit(resetTerm);
    initTerm();
    hideCursor();
    
    loadUsers();
    loadScores();
    loadEnemyTypes();

    displayLandingPage();

    int selection = 0;
    while (true) {
        clearScreen();
        gotoxy(20, 2); printf("HoloKron");
        if (currentUser) {
            gotoxy(15, 4); printf("Welcome, %s!", currentUser->username);
            char* options[] = {"Play Game", "Leaderboard", "How to Play", "Logout"};
            for (int i = 0; i < 4; i++) {
                gotoxy(20, 6 + i);
                if (i == selection) printf(">> %s <<", options[i]);
                else printf("   %s   ", options[i]);
            }
            fflush(stdout);
            
            int key = waitKey();
            if (key == 1000) selection = (selection - 1 + 4) % 4;
            else if (key == 1001) selection = (selection + 1) % 4;
            else if (key == 13) {
                if (selection == 0) playGame();
                else if (selection == 1) showLeaderboard();
                else if (selection == 2) showHowToPlay();
                else if (selection == 3) currentUser = NULL;
                selection = 0;
            }
        } else {
            char* options[] = {"Login", "Register", "Leaderboard", "How to Play", "Exit"};
            for (int i = 0; i < 5; i++) {
                gotoxy(20, 6 + i);
                if (i == selection) printf(">> %s <<", options[i]);
                else printf("   %s   ", options[i]);
            }
            fflush(stdout);
            
            int key = waitKey();
            if (key == 1000) selection = (selection - 1 + 5) % 5;
            else if (key == 1001) selection = (selection + 1) % 5;
            else if (key == 13) {
                if (selection == 0) handleLogin();
                else if (selection == 1) handleRegister();
                else if (selection == 2) showLeaderboard();
                else if (selection == 3) showHowToPlay();
                else if (selection == 4) break;
                selection = 0;
            }
        }
    }
    return 0;
}
