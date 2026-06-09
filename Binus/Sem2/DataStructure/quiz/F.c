#include <stdio.h>
#include <string.h>

#define TABLE_SIZE 5

typedef struct {
    char alphabet;
    int frequency;
    int is_occupied; 
} HashEntry;

HashEntry hashTable[TABLE_SIZE];

void initHashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i].alphabet = '\0';
        hashTable[i].frequency = 0;
        hashTable[i].is_occupied = 0;
    }
}

void insertCharacter(char c) {
    int index = c % TABLE_SIZE;
    int startIndex = index;

    while (hashTable[index].is_occupied) {
        if (hashTable[index].alphabet == c) {
            hashTable[index].frequency++;
            return;
        }
        index = (index + 1) % TABLE_SIZE;
        
        if (index == startIndex) {
            return; 
        }
    }

    hashTable[index].alphabet = c;
    hashTable[index].frequency = 1;
    hashTable[index].is_occupied = 1;
}

int main() {
    char s[1005];
    
    if (scanf("%s", s) != 1) {
        return 0;
    }

    initHashTable();

    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        insertCharacter(s[i]);
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i].is_occupied) {
            printf("%c %d\n", hashTable[i].alphabet, hashTable[i].frequency);
        }
    }

    return 0;
}