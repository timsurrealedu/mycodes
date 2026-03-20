#include <stdio.h>

struct tnode {
	int value;
	struct tnode *next;
};

struct tnode *head = 0;


//Insert
struct tnode *node =
(struct tnode*)
malloc(sizeof(struct tnode));
node->value = x;
node->next = head;
head = node;
