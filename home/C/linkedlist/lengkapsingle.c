#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

// ─────────────────────────────────────────
//  HELPER — create a new node
// ─────────────────────────────────────────
Node* createNode(int value) {
    Node* n = malloc(sizeof(Node));
    n->data = value;
    n->next = NULL;
    return n;
}

// ─────────────────────────────────────────
//  PUSH (insert)
// ─────────────────────────────────────────

// insert at the front
Node* pushHead(Node* head, int value) {
    Node* n = createNode(value);
    n->next = head;   // new node points to old head
    return n;         // new node becomes the new head
}

// insert at the end
void pushTail(Node* head, int value) {
    Node* n = createNode(value);
    Node* current = head;
    while (current->next != NULL)   // walk to the last node
        current = current->next;
    current->next = n;              // link last node to new node
}

// insert at a specific position (0 = head)
Node* pushMid(Node* head, int value, int position) {
    if (position == 0)
        return pushHead(head, value);   // reuse pushHead

    Node* n = createNode(value);
    Node* current = head;

    for (int i = 0; i < position - 1; i++) {  // walk to node BEFORE position
        if (current->next == NULL) {           // position out of range
            printf("Position out of range\n");
            return head;
        }
        current = current->next;
    }

    n->next = current->next;   // new node points to the node after
    current->next = n;         // previous node points to new node
    return head;
}

// ─────────────────────────────────────────
//  POP (delete)
// ─────────────────────────────────────────

// delete from the front
Node* popHead(Node* head) {
    if (head == NULL) {
        printf("List is empty\n");
        return NULL;
    }
    Node* temp = head;       // save old head
    head = head->next;       // move head forward
    free(temp);              // free old head
    return head;             // return new head
}

// delete from the end
void popTail(Node* head) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    if (head->next == NULL) {
        printf("Use popHead for single node\n");
        return;
    }
    Node* current = head;
    while (current->next->next != NULL)  // walk to second-to-last node
        current = current->next;
    free(current->next);     // free the last node
    current->next = NULL;    // second-to-last now points to NULL
}

// delete from a specific position (0 = head)
Node* popMid(Node* head, int position) {
    if (head == NULL) {
        printf("List is empty\n");
        return NULL;
    }
    if (position == 0)
        return popHead(head);   // reuse popHead

    Node* current = head;

    for (int i = 0; i < position - 1; i++) {  // walk to node BEFORE position
        if (current->next == NULL) {
            printf("Position out of range\n");
            return head;
        }
        current = current->next;
    }

    Node* temp = current->next;       // save the node to delete
    current->next = temp->next;       // skip over it
    free(temp);                       // free it
    return head;
}

// ─────────────────────────────────────────
//  UTILITY
// ─────────────────────────────────────────

void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int listLength(Node* head) {
    int count = 0;
    Node* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

// ─────────────────────────────────────────
//  MAIN — testing all operations
// ─────────────────────────────────────────

int main() {
    Node* head = NULL;  // start with empty list

    // push head
    printf("=== pushHead ===\n");
    head = pushHead(head, 10);
    head = pushHead(head, 20);
    head = pushHead(head, 30);
    printList(head);  // 30 -> 20 -> 10 -> NULL

    // push tail
    printf("=== pushTail ===\n");
    pushTail(head, 40);
    pushTail(head, 50);
    printList(head);  // 30 -> 20 -> 10 -> 40 -> 50 -> NULL

    // push mid (insert at position 2)
    printf("=== pushMid (pos 2) ===\n");
    head = pushMid(head, 99, 2);
    printList(head);  // 30 -> 20 -> 99 -> 10 -> 40 -> 50 -> NULL

    // pop head
    printf("=== popHead ===\n");
    head = popHead(head);
    printList(head);  // 20 -> 99 -> 10 -> 40 -> 50 -> NULL

    // pop tail
    printf("=== popTail ===\n");
    popTail(head);
    printList(head);  // 20 -> 99 -> 10 -> 40 -> NULL

    // pop mid (delete at position 1)
    printf("=== popMid (pos 1) ===\n");
    head = popMid(head, 1);
    printList(head);  // 20 -> 10 -> 40 -> NULL

    // length
    printf("=== length ===\n");
    printf("Length: %d\n", listLength(head));  // 3

    return 0;
}
// ```

// ---

// ## Expected Output
// ```
// === pushHead ===
// 30 -> 20 -> 10 -> NULL
// === pushTail ===
// 30 -> 20 -> 10 -> 40 -> 50 -> NULL
// === pushMid (pos 2) ===
// 30 -> 20 -> 99 -> 10 -> 40 -> 50 -> NULL
// === popHead ===
// 20 -> 99 -> 10 -> 40 -> 50 -> NULL
// === popTail ===
// 20 -> 99 -> 10 -> 40 -> NULL
// === popMid (pos 1) ===
// 20 -> 10 -> 40 -> NULL
// === length ===
// Length: 3
// ```

// ---

// ## Visual summary of each operation
// ```
// pushHead(30):   [30] -> NULL
// pushHead(20):   [20] -> [30] -> NULL
// pushTail(40):   [20] -> [30] -> [40] -> NULL
// pushMid(99, 1): [20] -> [99] -> [30] -> [40] -> NULL
//                           ↑
//                      inserted here

// popHead():      [99] -> [30] -> [40] -> NULL
// popTail():      [99] -> [30] -> NULL
// popMid(1):      [99] -> NULL
//                   ↑
//              deleted pos 1 ([30])