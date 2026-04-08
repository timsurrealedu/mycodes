#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_STRING

typedef struct node{
    char value[MAX_STRING];
    char key[MAX_STRING];
    struct node* prev;
    struct node* next;
}node;

void insert(char* item){
    int index = hashFunction(item);
    
}