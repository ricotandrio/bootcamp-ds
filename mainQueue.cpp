#include<stdio.h>
#include<stdlib.h>

struct Queue{
    int n;
    Queue *next, *prev;
}*front = NULL, *rear = NULL;

Queue *createNode(int n){
    Queue *newNode = (Queue*)malloc(sizeof(Queue));
    newNode->n = n;
    newNode->next = NULL;
    return newNode;
}

// ADD
void enqueue(Queue *createNode){
    if(front == NULL){
        front = rear = createNode;
    } else {
        rear->next = createNode;
        createNode->prev = rear;
        rear = createNode;
    }
}

// REMOVE
void dequeue(){ 
    if(front == NULL){
        return;
    } else {
        Queue *newFront = front->next;
        front = NULL;
        free(front);
        front = newFront;
    }
}

void display(){
    if(front == NULL){
        puts("NO DATA");
    } else {
        Queue *curr = front;
        while(curr != NULL){
            printf("%d->", curr->n);
            curr = curr->next;
        }
        puts("NULL");
    }
}

int main(){
    // INSERT
    enqueue(createNode(10));
    enqueue(createNode(40));
    enqueue(createNode(50));
    enqueue(createNode(20));
    enqueue(createNode(30));
    display();

    // REMOVE
    dequeue();
    dequeue();
    display();
    return 0;
}