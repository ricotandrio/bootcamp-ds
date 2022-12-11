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
    }
    else if(createNode->n >= front->n){
        createNode->next = front;
        front->prev = createNode;
        front = createNode;
    } 
    else if(createNode->n <= rear->n){
        rear->next = createNode;
        createNode->prev = rear;
        rear = createNode;
    }
    else {
        Queue *curr = front;
        while(curr->next != NULL){
            if(curr->n >= createNode->n && curr->next->n < createNode->n){
                break;
            }
            curr = curr->next;
        }
        Queue *afterCurr = curr->next;
        curr->next = createNode;
        createNode->prev = curr;

        createNode->next = afterCurr;
        afterCurr->prev = createNode;
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