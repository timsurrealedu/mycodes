#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
    int size; 
} Node;

int getHeight(Node *N) {
    if (N == NULL) return 0;
    return N->height;
}

int getSize(Node *N) {
    if (N == NULL) return 0;
    return N->size;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Node* createNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; 
    node->size = 1;   
    return node;
}

Node *rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    y->size = getSize(y->left) + getSize(y->right) + 1;
    x->size = getSize(x->left) + getSize(x->right) + 1;

    return x;
}

Node *leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    x->size = getSize(x->left) + getSize(x->right) + 1;
    y->size = getSize(y->left) + getSize(y->right) + 1;

    return y;
}

int getBalance(Node *N) {
    if (N == NULL) return 0;
    return getHeight(N->left) - getHeight(N->right);
}

Node* insert(Node* node, int key) {
    if (node == NULL)
        return createNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else 
        return node; 

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    node->size = 1 + getSize(node->left) + getSize(node->right);

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

Node * minValueNode(Node* node) {
    Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

Node* deleteNode(Node* root, int key) {
    if (root == NULL) return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            Node *temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else 
                *root = *temp; 
            
            free(temp);
        } else {
            Node* temp = minValueNode(root->right);

            root->key = temp->key;

            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == NULL) return root;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    root->size = 1 + getSize(root->left) + getSize(root->right);

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

int findKthSmallest(Node* root, int k) {
    if (root == NULL) return -1; 
    
    int leftSize = getSize(root->left);
    
    if (k == leftSize + 1) {
        return root->key;
    } else if (k <= leftSize) {
        return findKthSmallest(root->left, k);
    } else {
        return findKthSmallest(root->right, k - leftSize - 1);
    }
}

int main() {
    int N, Q, k;
    
    if (scanf("%d %d %d", &N, &Q, &k) != 3) {
        return 0;
    }

    Node* root = NULL;

    for (int i = 0; i < N; i++) {
        int val;
        scanf("%d", &val);
        root = insert(root, val);
    }

    for (int i = 0; i < Q; i++) {
        int remove_val;
        scanf("%d", &remove_val);
        
        root = deleteNode(root, remove_val);
        
        printf("%d\n", findKthSmallest(root, k));
    }

    return 0;
}