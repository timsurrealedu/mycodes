#include <stdio.h>
#include <stdlib.h>

// Cross-platform setup for input and screen clearing
#ifdef _WIN32
    #include <conio.h>
    #define CLEAR "cls"
#else
    #include <termios.h>
    #include <unistd.h>
    #define CLEAR "clear"

    // Manual getch() for Linux/Arch
    int getch() {
        struct termios oldt, newt;
        int ch;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
    }
#endif

#define ROWS 6
#define COLS 7

// Key Definitions for cross-platform logic
#define KEY_UP 1001
#define KEY_DOWN 1002
#define KEY_LEFT 1003
#define KEY_RIGHT 1004
#define KEY_ENTER 13
#define KEY_SPACE 32
#define KEY_ESC 27

int board[ROWS][COLS];
int cursorCol = 0;
int currentPlayer = 1;

// Function to handle key presses across different OS signals
int get_input() {
    int ch = getch();
    if (ch == 27) { 
        #ifdef _WIN32
            return ch; 
        #else
            // Linux arrow keys are escape sequences: ESC + [ + (A,B,C,D)
            int next = getch();
            if (next == 91) {
                switch (getch()) {
                    case 65: return KEY_UP;
                    case 66: return KEY_DOWN;
                    case 68: return KEY_LEFT;
                    case 67: return KEY_RIGHT;
                }
            }
            return KEY_ESC;
        #endif
    }
    // Handle Windows special keys (arrows) which start with 0 or 224
    #ifdef _WIN32
    if (ch == 0 || ch == 224) {
        int next = getch();
        switch (next) {
            case 72: return KEY_UP;
            case 80: return KEY_DOWN;
            case 75: return KEY_LEFT;
            case 77: return KEY_RIGHT;
        }
    }
    #endif
    return ch;
}

void initBoard() {
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            board[i][j] = 0;
}

// RECURSIVE WIN CONDITION
int countRecursive(int r, int c, int dr, int dc, int player) {
    if (r < 0 || r >= ROWS || c < 0 || c >= COLS || board[r][c] != player) {
        return 0;
    }
    return 1 + countRecursive(r + dr, c + dc, dr, dc, player);
}

int checkWin(int r, int c) {
    int player = board[r][c];
    int dirs[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}}; 

    for (int i = 0; i < 4; i++) {
        int count = 1; 
        count += countRecursive(r + dirs[i][0], c + dirs[i][1], dirs[i][0], dirs[i][1], player);
        count += countRecursive(r - dirs[i][0], c - dirs[i][1], -dirs[i][0], -dirs[i][1], player);
        if (count >= 4) return 1;
    }
    return 0;
}

void drawGame() {
    system(CLEAR);
    printf("--- Player %d's Turn ---\n\n", currentPlayer);

    // Disc preview above columns
    for (int j = 0; j < COLS; j++) {
        if (j == cursorCol) printf("  V  ");
        else printf("     ");
    }
    printf("\n");

    // Main 7x6 Grid
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == 0) printf("| . |");
            else printf("| %c |", (board[i][j] == 1) ? 'O' : 'X');
        }
        printf("\n");
    }
    printf("  1    2    3    4    5    6    7  \n\n");
    printf("Controls: [LEFT/RIGHT] to move | [SPACE] to drop | [ESC] to quit\n");
}

void playGame() {
    initBoard();
    currentPlayer = 1;
    cursorCol = 0;

    while (1) {
        drawGame();
        int input = get_input();

        if (input == KEY_ESC) return;

        if (input == KEY_LEFT) { if (cursorCol > 0) cursorCol--; }
        else if (input == KEY_RIGHT) { if (cursorCol < COLS - 1) cursorCol++; }
        
        else if (input == KEY_SPACE) {
            int rowPlaced = -1;
            for (int i = ROWS - 1; i >= 0; i--) {
                if (board[i][cursorCol] == 0) {
                    board[i][cursorCol] = currentPlayer;
                    rowPlaced = i;
                    break;
                }
            }

            if (rowPlaced != -1) {
                if (checkWin(rowPlaced, cursorCol)) {
                    drawGame();
                    printf("\nPLAYER %d WINS!\n", currentPlayer);
                    getch(); return;
                }
                
                int full = 1;
                for(int j=0; j<COLS; j++) if(board[0][j] == 0) full = 0;
                if(full) {
                    drawGame();
                    printf("\nIT'S A DRAW!\n");
                    getch(); return;
                }
                currentPlayer = (currentPlayer == 1) ? 2 : 1;
            }
        }
    }
}

void menu() {
    int choice = 0;
    char *options[] = {"Start Game", "Instructions", "Exit"};

    while (1) {
        system(CLEAR);
        printf("=== linHKup ===\n\n");
        for (int i = 0; i < 3; i++) {
            if (i == choice) printf(" >> %s << \n", options[i]);
            else printf("    %s    \n", options[i]);
        }

        int input = get_input();
        if (input == KEY_UP) choice = (choice + 2) % 3;
        else if (input == KEY_DOWN) choice = (choice + 1) % 3;
        else if (input == KEY_ENTER || input == KEY_SPACE) {
            if (choice == 0) playGame();
            else if (choice == 1) {
                system(CLEAR);
                printf("Instructions:\n1. Use arrows to move.\n2. Space to drop.\n3. Connect 4 to win.\n\nPress any key...");
                getch();
            } else exit(0);
        }
    }
}

int main() {
    menu();
    return 0;
}