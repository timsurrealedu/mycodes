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
        return;
    }
    if(tail->value==value){
        popTail();
        return;
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

void viewNode(){
    node* curr = head;
    while(curr){
        printf("%d ",curr->value);
        curr=curr->next;
    }
    printf("\n");
}

void clearNode(){
    node* curr = head;
    while(curr){
        node* temp = curr;
        curr =  curr->next;
        free(temp);
        curr->prev = NULL;
    }
}

int main(){
    int option=0;
    int value;
    while(option != 7){
        printf("what do you want to do?\n1. Push Head\n2. Push Tail\n3. Pop Head\n4. Pop Tail\n5. View Node\n");

        scanf("%d",&option);
        switch(option){
            case 1:
            printf("enter value: ");
            scanf("%d",&value);getchar();
            pushHead(value);
            break;
            case 2:
            printf("enter value: ");
            scanf("%d", &value);getchar();
            pushTail(value);
            break;
            case 3:
            popHead();
            break;
            case 4:
            popTail();
            break;
            case 5: 
            viewNode();
            break;
            case 6:
            clearNode();
            break;

        }

    }
   }


