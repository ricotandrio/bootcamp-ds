#include<stdio.h>
#include<stdlib.h>

struct Stack{
    int n;
    Stack *up, *down;
}*top = NULL, *bottom = NULL;

Stack *createNode(int n){
    Stack *newNode = (Stack*) malloc(sizeof(Stack));
    newNode->n = n;
    newNode->up = NULL;
    return newNode;
}

void pushTop(Stack *createNode){
    if(bottom == NULL){
        top = bottom = createNode;
    } else {
        top->up = createNode;
        createNode->down = top;
        top = createNode;
    }
}

void pushBottom(Stack *createNode){
    if(bottom == NULL){
        top = bottom = createNode;
    } else {
        createNode->up = bottom;
        bottom->down = createNode;
        bottom = createNode;
    }
}

void pushMid(Stack *createNode){
    if(bottom == NULL){
        top = bottom = createNode;
    }
    else if(createNode->n <= bottom->n){
        pushBottom(createNode);
    }
    else if(createNode->n >= top->n){
        pushTop(createNode);
    }
    else {
        Stack *curr = bottom;
        while(curr->up != NULL){
            if(createNode->n >= curr->n && createNode->n < curr->up->n){
                break;
            }
            curr = curr->up;
        }
        Stack *afterCurr = curr->up;
        curr->up = createNode;
        createNode->down = curr;

        createNode->up = afterCurr;
        afterCurr->down = createNode;
    }
}

void popTop(){
    if(bottom == NULL){
        return;
    }
    else if(bottom == top){
        bottom->up = top->down = NULL; // DELETE ARROW
        free(bottom);
    }
    else {
        Stack *newTop = top->down;
        newTop->up = top->down = NULL; // DELETE ARROW
        free(top);
        top = newTop;
    }
}

void popBottom(){
    if(bottom == NULL){
        return;
    }
    else if(bottom == top){
        bottom->up = top->down = NULL; // DELETE ARROW
        free(bottom);
    }
    else {
        Stack *newBottom = bottom->up;
        newBottom->down = bottom->up = NULL; // DELETE ARROW
        free(bottom);
        bottom = newBottom;
    }
}

void popMid(Stack *createNode){
    if(bottom == NULL){
        return;
    }
    else if(createNode->n == bottom->n){
        popBottom();
    }
    else if(createNode->n == top->n){
        popTop();
    }
    else {
        Stack *curr = bottom;
        while(curr->up != NULL){
            if(curr->n == createNode->n){
                break;
            }
            curr = curr->up;
        }
        if(curr == top) puts("DATA NOT FOUND"); return;
        Stack *beforeCurr = curr->down;
        Stack *afterCurr = curr->up;
        curr->up = curr->down = NULL; // DELETE ARROW
        free(curr);
        beforeCurr->up = afterCurr;
        afterCurr->down = beforeCurr;
    }
}

void display(){
    if(top == NULL){
        puts("NO DATA");
    } else {
        Stack *curr = top;
        while(curr != NULL){
            printf(" %d\n", curr->n);
            puts("===");
            curr = curr->down;
        }
        puts("NULL");
    }
}

int main(){
    puts("Display #1:");
    pushTop(createNode(6));
    pushTop(createNode(8));
    pushBottom(createNode(5));
    pushBottom(createNode(4));
    pushMid(createNode(6));
    pushMid(createNode(20));
    pushMid(createNode(12));
    pushMid(createNode(4));
    display();
    // puts("\nDisplay #2:");
    // popBottom();
    // popMid(createNode(4));
    // display();
    return 0;
}