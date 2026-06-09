#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void insertEnd(Node** head, Node** tail, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        *tail = newNode;
    } else {
        (*tail)->next = newNode;
        newNode->prev = *tail;
        *tail = newNode;
    }
}

void deleteOdds(Node** head, Node** tail) {
    Node* curr = *head;
    
    while (curr != NULL) {
        if (curr->data % 2 != 0) { 
            Node* nodeToDelete = curr;
            
            if (curr->prev != NULL) {
                curr->prev->next = curr->next;
            } else {
                *head = curr->next;
            }
            if (curr->next != NULL) {
                curr->next->prev = curr->prev;
            } else {
                *tail = curr->prev;
            }
            
            curr = curr->next;
            free(nodeToDelete);
        } else {
            curr = curr->next;
        }
    }
}

int main() {
    int n;
    
    if (scanf("%d", &n) != 1) {
        return 0;
    }

    Node* head = NULL;
    Node* tail = NULL;

    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        insertEnd(&head, &tail, val);
    }

    deleteOdds(&head, &tail);

    if (head == NULL) {
        printf("-1\n");
    } else {
        Node* curr = head;
        while (curr != NULL) {
            printf("%d", curr->data);
            if (curr->next != NULL) {
                printf(" ");
            }
            curr = curr->next;
        }
        printf("\n");
    }

    Node* curr = head;
    while (curr != NULL) {
        Node* temp = curr;
        curr = curr->next;
        free(temp);
    }

    return 0;
}