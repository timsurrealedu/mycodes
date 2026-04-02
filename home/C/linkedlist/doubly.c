#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int value;
    struct node* next;
    struct node* prev;
}node;

node* head=NULL, *tail=NULL;

node* createNode(int value){
    node* newNode = (node*)malloc(sizeof(node));
    newNode->value=value;
    newNode->next=NULL;
    newNode->prev=NULL;
    return newNode;
}

void pushHead(int value){
    node* newNode = createNode(value);
    if(head==NULL){
        head=tail=newNode;
        return;
    }
    newNode->next=head;
    head->prev=newNode;
    head=newNode;
}

void pushTail(int value){
    node* newNode = createNode(value);
    if(tail==NULL){
        head=tail=newNode;
        return;
    }
    tail->next=newNode;
    newNode->prev=tail;
    tail=newNode;
}

void pushSort(int value){
    node* newNode = createNode(value);
    if(head==NULL){
        head=tail=newNode;
        return;
    }
    if(head->value>=value){
        newNode->next=head;
        head->prev=newNode;
        head=newNode;
        return;
    }
    if(tail->value<=value){
        tail->next=newNode;
        newNode->prev=tail;
        tail=newNode;
        return;
    }

    node* curr = head;
    while(curr->next->value<=value){
        curr=curr->next;
    }
    newNode->prev=curr;
    newNode->next=curr->next;
    curr->next->prev=newNode;
    curr->next=newNode;
}

void popHead(){
    if(head==NULL){
        printf("nothing to pop\n");
        return;
    }if(head==tail){
        free(head);
        head=tail=NULL;
        return;
    }
    node* temp = head;
    head=head->next;
    head->prev=NULL;
    free(temp);
}

void popTail(){
    if(head==NULL){
        printf("nothing to pop\n");
        return;
    }if(head==tail){
        free(head);
        head=tail=NULL;
        return;
    }
    node* temp = tail;
    tail = tail->prev;
    tail->next = NULL;
    free(temp);
}

void popSearch(int value){
    if(head==NULL){
        printf("nothing to pop\n");
        return;
    }

    if(head->value==value){
        popHead();
    }
    if(tail->value==value){
        popTail();
    }
    node* curr = head;
    while (curr->next != NULL && curr->next->value != value) {
        curr = curr->next;
    }

    // 3. Check if we actually found it
    if (curr->next == NULL) {
        printf("Value %d not found\n", value);
        return;
    }

    // 4. Perform the "surgery"
    node* temp = curr->next;      // The node to die
    curr->next = temp->next;      // Skip over it (forward)
    
    if (temp->next != NULL) {     // Safety check (though tail check covers this)
        temp->next->prev = curr;  // Skip over it (backward)
    }

    free(temp);

}




