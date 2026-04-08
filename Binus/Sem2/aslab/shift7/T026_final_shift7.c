#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct State {
    int turn;
    int playerHP;
    int enemyHP;
    int skillsLeft;
    struct State* prev;
    struct State* next;
}State;

State* currentState = NULL;

void clearScreen() {
    printf("\033[H\033[2J"); 
}

void saveTurn(int t, int pHP, int eHP, int skills) {
    State* newNode = (State*)malloc(sizeof(State));
    newNode->turn = t;
    newNode->playerHP = pHP;
    newNode->enemyHP = eHP;
    newNode->skillsLeft = skills;
    newNode->next = NULL;
    newNode->prev = currentState;

    if (currentState != NULL) {
        State* future = currentState->next;
        while (future != NULL) {
            State* temp = future;
            future = future->next;
            free(temp); 
        }
        currentState->next = newNode;
    }
    
    currentState = newNode;
}



int main() {
    srand(time(NULL)); 
    
    int menuChoice = 0;
    char playerName[50];
    int difficulty;
    int enemyBaseDamage;

    while (menuChoice != 2) {
        clearScreen();
        printf("=======================\n");
        printf("       FURNBASE        \n");
        printf("=======================\n");
        printf("1. Start New Game      \n");
        printf("2. Exit Application    \n");
        printf("Choice >> ");
        scanf("%d", &menuChoice);

        if (menuChoice == 1) {
            clearScreen();
            
            printf("PLAYER SETUP\n");
            printf("Enter Player Name (No Spaces): ");
            scanf("%s", playerName); 

            printf("\nSELECT DIFFICULTY\n");
            printf("1. Easy\n2. Normal\n3. Hard\n");
            printf("Selection >> ");
            scanf("%d", &difficulty);

            enemyBaseDamage = 10 + (difficulty * 5);

            int pHP = 200;
            int eHP = 200; 
            int skills = 3; 
            int turn = 1;
            
            currentState = NULL;
            saveTurn(turn, pHP, eHP, skills);

            int battleActive = 1;

            while (battleActive) {
                clearScreen();
                
                char aiMode[20];
                if (eHP > 60) strcpy(aiMode, "Aggressive");
                else if (eHP > 30) strcpy(aiMode, "Balanced");
                else strcpy(aiMode, "Defensive");

                printf("Player: %s | Turn: %d | Skills: %d/3\n", playerName, turn, skills);
                printf("PLAYER HP: %d\n", pHP);
                printf("ENEMY HP : %d\n", eHP);
                printf("AI Mode: %s\n", aiMode);
                printf("----------------------------------\n");
                printf("[1] ATTACK  [2] DEFEND  [3] SKILL\n");
                printf("[u] UNDO    [r] REDO    [q] QUIT\n");
                printf("Select Move >> ");
                
                char action;
                scanf(" %c", &action);

                int pDamageDealt = 0;
                int pBlock = 0;
                int eDamageDealt = 0;
                int eBlock = 0;
                int validMove = 0; 

                if (action == 'u') {
                    if (currentState->prev != NULL) {
                        currentState = currentState->prev;
                        pHP = currentState->playerHP;
                        eHP = currentState->enemyHP;
                        skills = currentState->skillsLeft;
                        turn = currentState->turn;
                    }
                    continue; 
                } 
                else if (action == 'r') {
                    if (currentState->next != NULL) {
                        currentState = currentState->next;
                        pHP = currentState->playerHP;
                        eHP = currentState->enemyHP;
                        skills = currentState->skillsLeft;
                        turn = currentState->turn;
                    }
                    continue; 
                }
                else if (action == 'q') {
                    break; 
                }
                if (action == '1') {
                    pDamageDealt = 25; 
                    validMove = 1;
                } 
                else if (action == '2') {
                    pBlock = 12; 
                    validMove = 1;
                } 
                else if (action == '3') {
                    if (skills > 0) {
                        pDamageDealt = 50;
                        skills--;
                        validMove = 1;
                    } else {
                        continue; 
                    }
                } 
                else {
                    continue; 
                }

                if (validMove) {
                    int aiRoll = rand() % 100; 
                    
                    if (strcmp(aiMode, "Aggressive") == 0) {
                        if (aiRoll < 60) eDamageDealt = enemyBaseDamage; 
                        else if (aiRoll < 80) eDamageDealt = enemyBaseDamage * 2; 
                        else eBlock = 12; 
                    } 
                    else if (strcmp(aiMode, "Balanced") == 0) {
                        if (aiRoll < 30) eDamageDealt = enemyBaseDamage; 
                        else if (aiRoll < 50) eDamageDealt = enemyBaseDamage * 2; 
                        else eBlock = 12; 
                    } 
                    else if (strcmp(aiMode, "Defensive") == 0) {
                        if (aiRoll < 30) eDamageDealt = enemyBaseDamage; 
                        else if (aiRoll < 80) eDamageDealt = enemyBaseDamage * 2;
                        else eBlock = 12; 
                    }

                    int pFinalDmg = pDamageDealt - eBlock;
                    if (pFinalDmg < 0) pFinalDmg = 0;
                    
                    int eFinalDmg = eDamageDealt - pBlock;
                    if (eFinalDmg < 0) eFinalDmg = 0;

                    eHP -= pFinalDmg;
                    pHP -= eFinalDmg;

                    if (eHP < 0) eHP = 0;
                    if (pHP < 0) pHP = 0;

                    turn++;
                    saveTurn(turn, pHP, eHP, skills);

                    if (eHP <= 0 || pHP <= 0) {
                        clearScreen();
                        if (eHP <= 0 && pHP > 0) {
                            printf(">>> VICTORY ACHIEVED <<<\n"); 
                        } else {
                            printf(">>> GAME OVER - DEFEAT <<<\n"); 
                        }
                        printf("Press Enter to return to menu...\n");
                        while(getchar() != '\n'); 
                        getchar(); 
                        battleActive = 0; 
                    }
                }
            }
        } 
        else if (menuChoice == 2) {
            printf("\nTerminating program...\n");
        }
    }

    return 0;
}