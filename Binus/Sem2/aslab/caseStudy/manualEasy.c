#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include <stdio.h>

void clearScreen() {
    // \e[1;1H moves the cursor to row 1, column 1
    // \e[2J clears the entire screen
    printf("\033[1;1H\033[2J");
}

void mainMenu(){
    printf("=== linHKup ===\n\n");
    printf("Start Game\n");
    printf("Instruction\n");
}

void chooseMenu(char arrow){
    if(arrow='s')
}