#include <stdio.h>
#include <stdlib.h>

typedef struct node{
  int value;
  struct node* next;
}node;

node* head = NULL, *tail=NULL;

node* createNode(int value){
  node* newNode = (node*)malloc(sizeof(node));
  newNode->value=value;
  newNode->next=NULL;
  return newNode;
}

void pushHead(int value){
  node* newNode = createNode(value);
  if(head==NULL){
    head=tail=newNode;
  }else{
    newNode->next=head;
    head=newNode;
  }

  void pushTail(int value){
    node* newNode = createNode(value);
    if(tail==NULL){
      head=tail=newNode;
    }
    else{
      tail->next=newNode;
      tail=newNode;
    }
  }

  void pushSort(int value){
    node* newNode = createNode(value);
    if(head==NULL){
      head=tail=newNode;
    }
    else if(head->value>=value){
      newNode->next=head;
      head=newNode;
    }
    else if(tail->value<=value){
      tail->next=newNode;
      tail=newNode;
    }
    else{
      node* back = head;
      node* curr = head->next;
      while(curr!=NULL&&curr->value<value){
        back=curr;
        curr=curr->next;
      }
      back->next=newNode;
      newNode->next=curr;
    }
  }

  void popHead(){
    if(head==NULL){
      printf("head is empty\n");
      return;
    }
    node* temp = head;
    head=head->next;
    free(temp);
    if(head==NULL) tail=NULL;
  }

  void popTail(){
    if(head==NULL){
      printf("head is empty\n");
      return;
    }
    else if(head==tail){
      free(head);
      head = tail = NULL;
      return;
    }
    node* curr = head;
    while(curr->next!=tail){
      curr=curr->next;
    }
    free(tail);
    tail=curr;
    tail->next=NULL;
  }

  void popSearch(int value){
    if(head==NULL) {
      printf("head is null\n");
      return;
    }
    if(head->value == value){
      node* temphead = head;
      head = head->next;
      free(temphead);
      return;
    }

    node* curr = head;
    while(curr->next!=NULL){
      if(curr->next->value == value){
        node* temp = curr->next;
        curr->next = curr->next->next;
        free(temp);
        return;
      }
      curr=curr->next; 
    }
    printf("not found\n");
  }

  void viewPlane(){
    if(head==NULL){
      printf("empty list\n");
      return;
    }
    node* curr = head;
    while(curr){
      printf("%d\n", curr->value);
      curr->next;
    }
  }

  int main(){
    pushHead(10);
    pushHead(100);
    pushHead(12);
    pushTail(2);

    viewPlane();
    return 0;
  }


  

}
