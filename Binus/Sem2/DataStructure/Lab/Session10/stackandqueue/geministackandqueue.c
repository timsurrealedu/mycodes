#include <stdio.h>
#include <stdlib.h> // Needed for malloc and free
#include <assert.h> // Needed for the assert() function

// 1. Define the Node
struct node {
    int val;
    struct node *next;
};

// 2. Initialize a node
void initnode(struct node *n, int val) {
    n->val = val;
    n->next = NULL; // Fixed: 'null' should be 'NULL' in C
}

// 3. Define the Stack
struct stack {
    struct node *head;
};

// 4. Check if stack is empty
int isempty(struct stack *st) {
    return st->head == NULL; // Fixed 'null' to 'NULL'
}

// 5. Initialize the stack
void initstack(struct stack *st) {
    st->head = NULL; // Fixed 'null' to 'NULL'
}

// 6. Push (Add an item to the top)
void push(struct stack *st, int val) {
    // Request memory for a new node
    struct node *new_node = (struct node*)malloc(sizeof(struct node));
    
    // Set its value
    initnode(new_node, val);
    
    // Make the new node point to the current top of the stack
    new_node->next = st->head;
    
    // Update the stack so its 'head' points to our new node
    st->head = new_node;
}

// 7. Pop (Remove an item from the top)
void pop(struct stack *st) {
    // If it's already empty, do nothing
    if (isempty(st)) {
        return; 
    }
    
    // Temporarily hold onto the current top node
    struct node *old_top = st->head;
    
    // Move the stack's head pointer down to the next node
    st->head = st->head->next;
    
    // Give the memory of the old top node back to the computer
    free(old_top);
}

// 8. Top (Look at the top item)
int top(struct stack *st) {
    assert(st->head != NULL); // Crash safely if empty
    return st->head->val;
}

// 9. Main Function (Testing it out)
int main() {
    // Create a stack variable
    struct stack my_stack;
    
    // Initialize it
    initstack(&my_stack);
    
    printf("Pushing 10, 20, and 30 onto the stack...\n");
    push(&my_stack, 10);
    push(&my_stack, 20);
    push(&my_stack, 30);
    
    printf("The top item is currently: %d\n", top(&my_stack)); // Should be 30
    
    printf("Popping the top item...\n");
    pop(&my_stack); // Removes 30
    
    printf("The top item is now: %d\n", top(&my_stack)); // Should be 20
    
    return 0;
}