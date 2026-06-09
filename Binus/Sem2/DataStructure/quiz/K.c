#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int id;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
} Queue;

void initQueue(Queue* q) {
    q->head = NULL;
    q->tail = NULL;
}

void pushNode(Queue* q, Node* n) {
    n->next = NULL;
    if (q->tail == NULL) {
        q->head = n;
        q->tail = n;
    } else {
        q->tail->next = n;
        q->tail = n;
    }
}

Node* popNode(Queue* q) {
    if (q->head == NULL) return NULL;
    Node* temp = q->head;
    q->head = q->head->next;
    if (q->head == NULL) {
        q->tail = NULL; 
    }
    temp->next = NULL;
    return temp;
}

void insertValue(Queue* q, int id) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->id = id;
    pushNode(q, newNode);
}

int compareInts(const void* a, const void* b) {
    int valA = *(const int*)a;
    int valB = *(const int*)b;
    if (valA < valB) return -1;
    if (valA > valB) return 1;
    return 0;
}

int isCancelled(int* arr, int size, int target) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return 1;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return 0;
}

int main() {
    int n, m;
    
    if (scanf("%d %d", &n, &m) != 2) return 0;
    
    Queue onlineQ, walkinQ, hybridQ;
    initQueue(&onlineQ);
    initQueue(&walkinQ);
    initQueue(&hybridQ);
    
    for (int i = 0; i < n; i++) {
        int id;
        scanf("%d", &id);
        insertValue(&onlineQ, id);
    }
    
    for (int i = 0; i < m; i++) {
        int id;
        scanf("%d", &id);
        insertValue(&walkinQ, id);
    }
    
    while (onlineQ.head != NULL || walkinQ.head != NULL) {
        if (onlineQ.head != NULL) {
            pushNode(&hybridQ, popNode(&onlineQ));
        }
        if (walkinQ.head != NULL) {
            pushNode(&hybridQ, popNode(&walkinQ));
        }
    }
    
    int l;
    if (scanf("%d", &l) != 1) return 0;
    
    if (l > 0) {
        int* cancelledList = (int*)malloc(l * sizeof(int));
        for (int i = 0; i < l; i++) {
            scanf("%d", &cancelledList[i]);
        }
        
        qsort(cancelledList, l, sizeof(int), compareInts);
        
        Node* curr = hybridQ.head;
        Node* prev = NULL;
        
        while (curr != NULL) {
            if (isCancelled(cancelledList, l, curr->id)) {
                Node* nodeToDelete = curr;
                
                if (prev == NULL) {
                    hybridQ.head = curr->next;
                } else {
                    prev->next = curr->next;
                }
                
                if (hybridQ.tail == curr) {
                    hybridQ.tail = prev;
                }
                
                curr = curr->next;
                free(nodeToDelete); 
            } else {
                prev = curr;
                curr = curr->next;
            }
        }
        
        free(cancelledList);
    }
    
    Node* curr = hybridQ.head;
    while (curr != NULL) {
        printf("%d", curr->id);
        if (curr->next != NULL) {
            printf(" ");
        }
        
        Node* temp = curr;
        curr = curr->next;
        free(temp);
    }
    printf("\n");
    
    return 0;
}