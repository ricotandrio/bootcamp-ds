#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct data {
    int date, month, year;
    char name[100];
    struct data *next, *prev;
}*head=NULL, *tail=NULL, *temp=NULL;

void popHead();
void popAll();
void printAll();
void addData();
void priorityPush(int date, int month, int year, const char *name);
int getMonthNumber(const char *month);
const char* getMonthName(int month);
long getDateNumber(int date, int month, int year);
struct data *createNode(int date, int month, int year, const char* name);

long getDateNumber(int date, int month, int year) {
    return (long)(year*10000)+(month*100)+date;
}

int getMonthNumber(const char *month) {
    if(!strcmp(month, "january")) return 1;
    if(!strcmp(month, "february")) return 2;
    if(!strcmp(month, "march")) return 3;
    if(!strcmp(month, "april")) return 4;
    if(!strcmp(month, "may")) return 5;
    if(!strcmp(month, "june")) return 6;
    if(!strcmp(month, "july")) return 7;
    if(!strcmp(month, "august")) return 8;
    if(!strcmp(month, "september")) return 9;
    if(!strcmp(month, "october")) return 10;
    if(!strcmp(month, "november")) return 11;
    if(!strcmp(month, "december")) return 12;
    
}

const char *getMonthName(int month) {
    switch(month) {
        case 1: 
            return "january";
        case 2: 
            return "february";
        case 3:     
            return "march";
        case 4: 
            return "april";
        case 5: 
            return "may";
        case 6: 
            return "june";
        case 7: 
            return "july";
        case 8: 
            return "august";
        case 9: 
            return "september";
        case 10: 
            return "october";
        case 11: 
            return "november";
        case 12: 
            return "december";
    }
}

void popAll() {
    while(head)
        popHead();
}

void printAll() {
    temp = head;
    while(temp != NULL) {
        printf("%d %s %d - %s\n", temp->date,
        getMonthName(temp->month), temp->year, temp->name);
        temp = temp->next;
   }
}

void addData() {
    int date, year;
    char month[100], name[100];
    scanf("%d %s %d - %[^\n]", &date, month, &year, name);
    getchar();
    priorityPush(date, getMonthNumber(month), year, name);
}

struct data *createNode(int date, int month, int year, const char *name)
{
    struct data *newNode = (struct data *) malloc(sizeof(struct data));
    newNode->date = date;
    newNode->month = month;
    newNode->year = year;
    strcpy(newNode->name, name);
    newNode->next = NULL;
    return newNode;
}

void priorityPush(int date, int month, int year, const char *name) {
    struct data *newNode = createNode(date, month, year, name);
    if(head == NULL){
        head = tail = newNode;
    }
    else if(getDateNumber(date, month, year) <= getDateNumber(head->date, head->month, head->year)){
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    else if(getDateNumber(date, month, year) >= getDateNumber(tail->date, tail->month, tail->year)){
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    else {
        struct data *curr = head;
        while(curr->next != NULL){
            if(getDateNumber(date, month, year) >= getDateNumber(curr->date, curr->month, curr->year) && getDateNumber(date, month, year) < getDateNumber(curr->next->date, curr->next->month, curr->next->year)){
                break;
            }
            curr = curr->next;
        }
        struct data *afterCurr = curr->next;
        curr->next = newNode;
        newNode->prev = curr;
        
        newNode->next = afterCurr;
        afterCurr->prev = newNode;
    }
}

void popHead() {
    if(head == NULL){
        return;
    } else {
        struct data *newHead = head->next;
        free(head);
        head->next = newHead->prev = NULL;
        head = newHead;
    }
}

int main() {
    int totalPatients, totalCure;
    scanf("%d %d", &totalPatients, &totalCure); getchar();
    for(int i=0; i<totalPatients; i++)
        addData();
    for(int i=0; i<totalCure; i++)
        popHead();
    if(totalPatients < totalCure || totalPatients == totalCure)
        printf("All patients get the cure, %d cure left\n",totalCure-totalPatients);
    else if(totalPatients > totalCure)
        printf("Need %d more cure\n", totalPatients - totalCure);
    printAll();
    // popAll();
}