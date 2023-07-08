#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// m = table size
int m = 23;

struct tnode{
    char value[10];
    int step;
}*ND[25];

int hashing(const char *value){
    int key = 0;
    int len = strlen(value);
    for(int i = 0; i < len; i++){
        key += value[i] - 'A';
    }
    // key %= m;
    return key%m;
}

struct tnode *newData(const char *value){
    tnode *ND = (tnode *) malloc(sizeof(tnode));
    strcpy(ND->value, value);
    return ND;
}

void insert(const char *value){
    struct tnode *N_Data = newData(value);
    int key = hashing(value);
    int temp = 1;
    if(!ND[key]){
        N_Data->step = temp;
        ND[key] = N_Data;
        return;
    } else {
        for(int i = (key+1)%m; i != key; i = (i + 1) % m){
            temp++;
            if(!ND[i]){
                N_Data->step = temp;
                ND[i] = N_Data;
                return;
            }
        }
    }
    puts("TABLE IS FULL");
}

void view(){
    for(int i = 0; i < m; i++){
        if(ND[i]) printf("[%d]\t%s (%d step(s))\n", i, ND[i]->value, ND[i]->step);
        else printf("[%d]\tNULL\n", i);
    }
}

int main(){
    for(int i = 0; i < m; i++){
        ND[i] = NULL;
    }
    insert("AAAAA");
    insert("BBBBB");
    insert("CCCCC");
    insert("AAABB");
    insert("BABAA");
    insert("BAABA");
    insert("BBAAA");
    insert("ABBAA");

    view();
    return 0;
}