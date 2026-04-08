#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

// --- Configuration & Constants ---
#define BOARD_WIDTH 60
#define BOARD_HEIGHT 25
#define STATS_OFFSET 65

// --- Structures following your style ---

// Enemy Bullet (Singly Linked List) [cite: 45]
struct SNode { 
    float x, y;
    float speed;
    struct SNode *next;
};

struct SLinkedList {
    struct SNode *head;
};

// Enemy Entity (Doubly Linked List) [cite: 43]
struct DNode {
    int x, y;
    char symbol[5];
    int score;
    struct DNode *next;
    struct DNode *prev;
};

struct DLinkedList {
    struct DNode *head;
    struct DNode *tail;
};

// --- Initializers following your style  ---

void initSNode(struct SNode *node, float x, float y, float speed) {
    node->x = x;
    node->y = y;
    node->speed = speed;
    node->next = NULL;
}

void initSLinkedList(struct SLinkedList *list) {
    list->head = NULL;
}

void initDNode(struct DNode *node, int x, int y, char* sym, int score) {
    node->x = x;
    node->y = y;
    strcpy(node->symbol, sym);
    node->score = score;
    node->next = NULL;
    node->prev = NULL;
}

void initDLinkedList(struct DLinkedList *list) {
    list->head = NULL;
    list->tail = NULL;
}

// --- List Operations following your logic [cite: 4, 16, 19] ---

void pushSHead(struct SLinkedList *list, float x, float y, float speed) {
    struct SNode *newNode = (struct SNode*)malloc(sizeof(struct SNode));
    initSNode(newNode, x, y, speed);
    newNode->next = list->head;
    list->head = newNode;
}

void pushDTail(struct DLinkedList *list, int x, int y, char* sym, int score) {
    struct DNode *newNode = (struct DNode*)malloc(sizeof(struct DNode));
    initDNode(newNode, x, y, sym, score);
    if (list->head == NULL) { [cite: 20]
        list->head = list->tail = newNode;
        return;
    }
    newNode->prev = list->tail; [cite: 21]
    list->tail->next = newNode;
    list->tail = newNode;
}

// O(1) Enemy Removal for collisions 
void removeDNode(struct DLinkedList *list, struct DNode *target) {
    if (target == list->head && target == list->tail) {
        list->head = list->tail = NULL;
    } else if (target == list->head) {
        list->head = target->next;
        list->head->prev = NULL;
    } else if (target == list->tail) {
        list->tail = target->prev;
        list->tail->next = NULL;
    } else {
        target->prev->next = target->next;
        target->next->prev = target->prev;
    }
    free(target);
}

// --- Game Engine Helpers [cite: 38] ---

void gotoxy(int x, int y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

// --- Core Game Logic ---

typedef struct {
    char symbol[5];
    int score;
} EnemyType;

EnemyType types[3];
int playerCount = 0;

void loadConfig() { [cite: 48, 50]
    // Mock parsing logic as per PRD requirements [cite: 52-54]
    strcpy(types[0].symbol, "<O>"); types[0].score = 10; // squid
    strcpy(types[1].symbol, "/W\\"); types[1].score = 20; // crab
    strcpy(types[2].symbol, "<M>"); types[2].score = 35; // octopus
}

int main() {
    srand(time(NULL));
    hideCursor();
    loadConfig();

    struct DLinkedList enemies;
    initDLinkedList(&enemies);
    struct SLinkedList eBullets;
    initSLinkedList(&eBullets);

    // Initial Enemy Grid [cite: 61]
    for(int row = 0; row < 3; row++) {
        for(int col = 0; col < 8; col++) {
            pushDTail(&enemies, 5 + (col * 6), 3 + (row * 2), types[row].symbol, types[row].score);
        }
    }

    int playerX = BOARD_WIDTH / 2;
    int pBulletX = -1, pBulletY = -1;
    int pBulletActive = 0; // 
    int score = 0, lives = 3; [cite: 62, 65]
    int dir = 1, frameCount = 0, pityTimer = 0;

    while (lives > 0) {
        // 1. Input [cite: 69, 71]
        if (_kbhit()) {
            char ch = _getch();
            if (ch == 75 && playerX > 1) playerX--; // Left
            if (ch == 77 && playerX < BOARD_WIDTH - 2) playerX++; // Right
            if (ch == ' ' && !pBulletActive) {
                pBulletActive = 1;
                pBulletX = playerX;
                pBulletY = BOARD_HEIGHT - 2;
            }
        }

        // 2. Logic: Player Bullet [cite: 73]
        if (pBulletActive) {
            pBulletY--;
            if (pBulletY < 1) pBulletActive = 0;
            
            // Player Bullet -> Enemy Collision [cite: 90, 92]
            struct DNode *cur = enemies.head;
            while (cur != NULL) {
                struct DNode *next = cur->next;
                if (pBulletX >= cur->x && pBulletX <= cur->x + 2 && pBulletY == cur->y) {
                    score += cur->score;
                    removeDNode(&enemies, cur);
                    pBulletActive = 0;
                    break;
                }
                cur = next;
            }
        }

        // 3. Logic: Enemy Movement [cite: 75, 76]
        if (frameCount % 10 == 0) {
            int hitBorder = 0;
            struct DNode *cur = enemies.head;
            while(cur != NULL) {
                if ((dir == 1 && cur->x >= BOARD_WIDTH - 4) || (dir == -1 && cur->x <= 1)) {
                    hitBorder = 1; break;
                }
                cur = cur->next;
            }
            
            cur = enemies.head;
            if (hitBorder) {
                dir *= -1;
                while(cur != NULL) { cur->y++; cur = cur->next; }
            } else {
                while(cur != NULL) { cur->x += dir; cur = cur->next; }
            }
        }

        // 4. Logic: Enemy Shooting [cite: 81, 82, 84]
        pityTimer++;
        int shootChance = rand() % 100;
        if (shootChance < 4 || pityTimer >= 35) {
            if (enemies.head != NULL) {
                // Simplified: shoot from a random existing enemy [cite: 79]
                struct DNode *shooter = enemies.head;
                for(int i=0; i < rand()%10 && shooter->next; i++) shooter = shooter->next;
                
                float speeds[] = {1.0f, 1.3f, 1.6f}; [cite: 84]
                pushSHead(&eBullets, (float)shooter->x + 1, (float)shooter->y + 1, speeds[rand()%3]);
                pityTimer = 0;
            }
        }

        // 5. Logic: Enemy Bullets [cite: 97, 98]
        struct SNode **indirect = &eBullets.head;
        while (*indirect != NULL) {
            struct SNode *b = *indirect;
            b->y += b->speed;
            
            if ((int)b->y == BOARD_HEIGHT - 1 && (int)b->x == playerX) {
                lives--; [cite: 97]
                *indirect = b->next;
                free(b);
            } else if (b->y >= BOARD_HEIGHT) {
                *indirect = b->next;
                free(b);
            } else {
                indirect = &((*indirect)->next);
            }
        }

        // 6. Rendering [cite: 57, 59]
        system("cls");
        // Draw Player
        gotoxy(playerX, BOARD_HEIGHT - 1); printf("=^=");
        
        // Draw Player Bullet
        if (pBulletActive) { gotoxy(pBulletX, pBulletY); printf("|"); }

        // Draw Enemies
        struct DNode *e = enemies.head;
        while(e != NULL) {
            gotoxy(e->x, e->y); printf("%s", e->symbol);
            e = e->next;
        }

        // Draw Enemy Bullets
        struct SNode *eb = eBullets.head;
        while(eb != NULL) {
            gotoxy((int)eb->x, (int)eb->y); printf("v");
            eb = eb->next;
        }

        // Draw Stats [cite: 62, 65]
        gotoxy(STATS_OFFSET, 5); printf("SCORE: %d", score);
        gotoxy(STATS_OFFSET, 7); printf("LIVES: %d", lives);

        frameCount++;
        Sleep(30);
    }

    // Game Over [cite: 103, 104]
    system("cls");
    gotoxy(BOARD_WIDTH/2 - 5, BOARD_HEIGHT/2);
    printf("GAME OVER! FINAL SCORE: %d", score);
    _getch();
    return 0;
}