#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    char parentheses;
    struct node* next;
}node;

node* head = NULL, *tail=NULL;

node* createNode(char parentheses){
    node* newNode = (node*)malloc(sizeof(node));
    newNode->parentheses=parentheses;
    newNode->next=NULL;
    return newNode;
}

void push(char parentheses){
    node* newNode = createNode(parentheses);
    if(head==NULL){
        head=tail=newNode;
        return;
    }
    newNode->next=head;
    head=newNode;
}

int pop(){
    if(head==NULL){
        printf("empty\n");
        return 0;
    }
    if(head==tail){
        free(head);
        head=tail=NULL;
        return 1;
    }
    node* temp = head;
    head = head->next;
    free(temp);
    return 1;
}

// void check(int value, char *parentheses){
//     for(int i=0;i<value;i++){
//         if(parentheses[i]=='('){
//             push(parentheses[i]);
//         }else if(parentheses[i]==')'){
//             int check = pop();
//             if(check == 0){
//                 printf("unbalanced\n");
//             }
//             else{
//                 printf("balanced\n");
//             }
//         }
        
//     }
// }

void check(int value, char *parentheses) {
    int is_possible = 1; // Assume it's balanced until proven otherwise

    for (int i = 0; i < value; i++) {
        if (parentheses[i] == '(') {
            push(parentheses[i]);
        } else if (parentheses[i] == ')') {
            if (pop() == 0) {
                // If we try to pop an empty stack, we have a ')' 
                // without a '(' roommate. It's over!
                is_possible = 0; 
                break; 
            }
        }
    }

    // FINAL VERDICT
    // It is ONLY balanced if:
    // 1. We never tried to pop an empty stack (is_possible == 1)
    // 2. The stack is empty now (no leftover '(' )
    if (is_possible && head == NULL) {
        printf("Balanced\n");
    } else {
        printf("Unbalanced\n");
    }

    // Memory Housekeeping: if it was unbalanced, 
    // there might be '(' left in the stack. Clear them!
    while (head != NULL) {
        pop();
    }
}

int main() {
    int capacity = 4; // Start with a small capacity to see the "growth" logic
    int length = 0;
    
    // Initial allocation
    char *input = (char *)malloc(capacity * sizeof(char));
    if (input == NULL) return 1;

    printf("Enter parentheses (press Enter to finish): ");

    char c;
    // Read characters one by one until a newline or End-Of-File
    while ((c = getchar()) != '\n' && c != EOF) {
        
        // If we are about to run out of space (reserve 1 byte for '\0')
        if (length + 1 >= capacity) {
            capacity *= 2; // Double the capacity
            
            // Reallocate the memory to the new, larger size
            char *temp = (char *)realloc(input, capacity * sizeof(char));
            if (temp == NULL) {
                free(input);
                return 1;
            }
            input = temp;
        }
        
        // Use pointer arithmetic or indexing to store the char
        *(input + length) = c; 
        length++;
    }

    // Crucial: Add the Null Terminator to make it a valid string
    *(input + length) = '\0';

    // Now call your check function with the dynamic length
    check(length, input);

    // Clean up the memory we borrowed from the heap
    free(input);

    return 0;
}