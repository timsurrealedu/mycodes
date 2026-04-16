#include <stdio.h>
#include <stdlib.h>

// Define a simple stack for the traversal
typedef struct {
    node** data;
    int top;
    int capacity;
} Stack;

Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->data = (node**)malloc(sizeof(node*) * capacity);
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

void push(Stack* stack, node* n) {
    if (stack->top < stack->capacity - 1) {
        stack->data[++(stack->top)] = n;
    }
}

node* pop(Stack* stack) {
    if (stack->top >= 0) {
        return stack->data[(stack->top)--];
    }
    return NULL;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

typedef struct node{
    int value;
    struct node* right;
    struct node* left;
} node;

node* createNode(int value){
    node* newNode = (node*)malloc(sizeof(node));
    newNode->value = value;
    newNode->right = NULL;
    newNode->left = NULL;
    return newNode;
}

node* insert(node* root, int value){
    node* newNode = createNode(value);
    if(root == NULL){
        return newNode;
    }
    node* curr = root;
    node* parent = NULL;

    while(curr != NULL){
        parent = curr;
        if(value < curr->value){
            curr = curr->left;
        } else if(value > curr->value){
            curr = curr->right;
        } else {
            // Duplicate found
            free(newNode);
            return root;
        }
    }
    
    if(value < parent->value){
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
    return root;
}

// FIXED ITERATIVE TRAVERSE
void traversePrint(node* root){
    if(root == NULL){
        printf("empty tree\n");
        return;
    }

    // We need a stack to remember nodes we haven't processed yet
    Stack* stack = createStack(100); // Assuming max depth 100 for simplicity
    node* curr = root;

    while (curr != NULL || !isEmpty(stack)) {
        // 1. Go as far left as possible, pushing nodes onto stack
        while (curr != NULL) {
            push(stack, curr);
            curr = curr->left;
        }

        // 2. Pop the top node (this is the next smallest)
        curr = pop(stack);
        printf("%d ", curr->value);

        // 3. Move to the right subtree
        curr = curr->right;
    }
    
    free(stack->data);
    free(stack);
}

int main(){
    node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 15);
    root = insert(root, 1);
    root = insert(root, 5); // Adding another node to test branching
    
    // Tree structure:
    //      10
    //     /  \
    //    1    15
    //     \
    //      5
    
    traversePrint(root); 
    // Expected Output: 1 5 10 15
    printf("\n");

    return 0;
}