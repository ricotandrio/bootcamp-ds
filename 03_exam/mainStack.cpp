#include<stdio.h>
#include<stdlib.h>

struct Stack{
    int n;
    Stack *up, *down;
}*top = NULL;

Stack *createNode(int n){
    Stack *newNode = (Stack*) malloc(sizeof(Stack));
    newNode->n = n;
    newNode->up = NULL;
    return newNode;
}

void pushTop(Stack *createNode){
    if(top == NULL){
        top = createNode;
    } else {
        top->up = createNode;
        createNode->down = top;
        top = createNode;
    }
}

void popTop(){
    if(top == NULL){
        return;
    }
    else if(top->down == NULL){
        free(top);
        top = NULL;
    }
    else {
        Stack *newTop = top->down;
        newTop->up = top->down = NULL; // DELETE ARROW
        free(top);
        top = NULL;
        top = newTop;
    }
}

void display(){
    if(top == NULL){
        puts("NO DATA");
    } else {
        puts("NULL");
        Stack *curr = top;
        while(curr != NULL){
            printf("%d\n", curr->n);
            puts("===");
            curr = curr->down;
        }
        puts("NULL");
    }
}

int main(){
    // INSERT
    puts("Display #1:");
    pushTop(createNode(8));
    pushTop(createNode(5));
    pushTop(createNode(10));
    pushTop(createNode(3));
    pushTop(createNode(21));
    pushTop(createNode(2));
    pushTop(createNode(15));
    display();

    // DELETE
    puts("\nDisplay #2:");
    popTop();
    popTop();
    display();
    return 0;
}