#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
} DoublyLinkedList;

void initList(DoublyLinkedList* list) {
    list->head = NULL;
    list->tail = NULL;
}

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void insertEnd(DoublyLinkedList* list, int data) {
    Node* newNode = createNode(data);
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        newNode->prev = list->tail;
        list->tail = newNode;
    }
}

void mergeLists(DoublyLinkedList* A, DoublyLinkedList* B) {
    if (A->head == NULL) {
        A->head = B->head;
        A->tail = B->tail;
    } else if (B->head != NULL) {
        A->tail->next = B->head;
        B->head->prev = A->tail;
        A->tail = B->tail;
    }
    
    B->head = NULL;
    B->tail = NULL;
}

void printAndFree(DoublyLinkedList* list) {
    Node* curr = list->head;
    while (curr != NULL) {
        printf("%d", curr->data);
        if (curr->next != NULL) {
            printf(" ");
        }
        
        Node* temp = curr;
        curr = curr->next;
        free(temp);
    }
    printf("\n");
}

int main() {
    int n, m;
    
    if (scanf("%d %d", &n, &m) != 2) {
        return 0;
    }
    
    DoublyLinkedList listA, listB;
    initList(&listA);
    initList(&listB);
    
    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        insertEnd(&listA, val);
    }
    
    for (int i = 0; i < m; i++) {
        int val;
        scanf("%d", &val);
        insertEnd(&listB, val);
    }
    
    mergeLists(&listA, &listB);
    
    printAndFree(&listA);
    
    return 0;
}