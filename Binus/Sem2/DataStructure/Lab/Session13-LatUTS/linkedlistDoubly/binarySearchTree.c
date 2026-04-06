#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode {
    int value;
    struct treeNode* left;
    struct treeNode* right;
} treeNode;

treeNode* root = NULL; // Only a root is needed!

// 1. Create a Node
treeNode* createNode(int value) {
    treeNode* newNode = (treeNode*)malloc(sizeof(treeNode));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 2. Insert (Iterative, similar to your list logic)
void insertNode(int value) {
    if (root == NULL) {
        root = createNode(value);
        return;
    }

    treeNode* curr = root;
    while (1) {
        if (value < curr->value) {
            if (curr->left == NULL) {
                curr->left = createNode(value);
                return;
            }
            curr = curr->left; // Go deeper left
        } 
        else if (value > curr->value) {
            if (curr->right == NULL) {
                curr->right = createNode(value);
                return;
            }
            curr = curr->right; // Go deeper right
        } 
        else {
            printf("Value %d already exists.\n", value);
            return; // BSTs usually ignore duplicates
        }
    }
}

// Helper Function: Find the smallest value in a subtree
treeNode* findMin(treeNode* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

// 3. Delete (Recursive - Much safer for trees)
treeNode* deleteHelper(treeNode* curr, int value) {
    // Base Case: Tree is empty or value not found
    if (curr == NULL) return curr;

    // Navigate the tree to find the node
    if (value < curr->value) {
        curr->left = deleteHelper(curr->left, value);
    } 
    else if (value > curr->value) {
        curr->right = deleteHelper(curr->right, value);
    } 
    else {
        // WE FOUND THE NODE TO DELETE!
        
        // Case 1 & 2: Node has 0 or 1 child
        if (curr->left == NULL) {
            treeNode* temp = curr->right;
            free(curr);
            return temp;
        } 
        else if (curr->right == NULL) {
            treeNode* temp = curr->left;
            free(curr);
            return temp;
        }

        // Case 3: Node has 2 children
        // Find the smallest value on the right side
        treeNode* temp = findMin(curr->right);
        
        // Copy that value into our current node
        curr->value = temp->value;
        
        // Delete the original duplicate node further down
        curr->right = deleteHelper(curr->right, temp->value);
    }
    return curr;
}

// Wrapper to make deletion easy to call from main
void deleteNode(int value) {
    root = deleteHelper(root, value);
}

// 4. View Nodes (In-Order Traversal prints them sorted!)
void viewTree(treeNode* curr) {
    if (curr != NULL) {
        viewTree(curr->left);          // Visit left
        printf("%d ", curr->value);    // Print self
        viewTree(curr->right);         // Visit right
    }
}

int main() {
    // Build the tree
    insertNode(50);
    insertNode(30);
    insertNode(70);
    insertNode(20);
    insertNode(40);
    insertNode(60);
    insertNode(80);

    printf("Tree before deletion: ");
    viewTree(root);
    printf("\n");

    // Test Deletions
    printf("\nDeleting 20 (Leaf Node)...\n");
    deleteNode(20);
    
    printf("Deleting 30 (Node with 1 child)...\n");
    deleteNode(30);

    printf("Deleting 50 (Root Node with 2 children!)...\n");
    deleteNode(50);

    printf("\nTree after deletions: ");
    viewTree(root);
    printf("\n");

    return 0;
}