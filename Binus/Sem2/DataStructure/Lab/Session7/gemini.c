#include <stdio.h>
#include <stdlib.h>

struct Node {
  int value;
  struct Node *next;
};

struct Node *createNode(int data) {
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

  newNode->value = data;
  newNode->next = NULL;
  return newNode;
}

void pushHead(struct Node **head, int data) {
  struct Node *newNode = createNode(data);

  newNode->next = *head;

  *head = newNode;
}

void pushTail(struct Node **head, int data) {
  struct Node *newNode = createNode(data);

  if (*head == NULL) {
    *head = newNode;
    return;
  }

  struct Node *temp = *head;
  while (temp->next != NULL) {
    temp = temp->next;
  }
  temp->next = newNode;
}

void popHead(struct Node **head) {
  if (*head == NULL) {
    printf("List is empty!\n");
    return;
  }
  struct Node *temp = *head;
  *head = (*head)->next;
  free(temp);
}

void popTail(struct Node **head) {
  if (*head == NULL)
    return;
  if ((*head)->next == NULL) {
    free(*head);
    *head = NULL;
    return;
  }

  struct Node *temp = *head;
  while (temp->next->next != NULL) {
    temp = temp->next;
  }
  free(temp->next);
  temp->next = NULL;
}

void printList(struct Node *head) {
  struct Node *temp = head;
  printf("List: ");
  while (temp != NULL) {
    printf("%d -> ", temp->value);
    temp = temp->next;
  }
  printf("NULL\n");
}

int main() {
  struct Node *head = NULL;
  pushHead(&head, 10);
  pushHead(&head, 20);
  pushTail(&head, 30);

  printList(head);

  popHead(&head);
  printList(head);
  popTail(&head);
  printList(head);
  return 0;
}