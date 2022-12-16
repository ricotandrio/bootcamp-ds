#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct data
{
    char value[100];
    struct data *next;
};

struct data *hashTables[31];

int hash(const char *str)
{
    int length = strlen(str);
    int base = 11;
    int MOD = 31;
    int key = 0;
    for(int i = 0; i < length; i++)
    {
        key = (key * base) + (str[i] - 'a' + 1);
        key = key % MOD;
    }
    return (key * base) % MOD;
}

void chaining(int idx,const char *str)
{
    struct data *newData = (struct data *) malloc(sizeof(struct data));
    strcpy(newData->value, str);
    newData->next = NULL;
    //INSERT YOUR CODE HERE, Insert Data into Hashtable with chaining
    if(!hashTables[idx]){
        hashTables[idx] = newData;
    } else {
        struct data *curr = hashTables[idx];
        while(curr->next != NULL){
            curr = curr->next;
        }
        curr->next = newData;
        newData->next = NULL;
    }
}

void viewAll()
{   
    //INSERT YOUR CODE HERE, View Data if the index have Data
    for(int i = 0; i < 31; i++){
        if(!hashTables[i] ) continue;
        else {
            struct data *curr = hashTables[i];
            printf("Index %d: ", i);
            while(curr){
                if(curr != NULL){
                    printf("%s", curr->value);
                }
                if(curr->next != NULL && curr != NULL){
                    printf(" -> ");
                }
                curr = curr->next;
            }
            puts("");
        }
    }
}

void popAll()
{
    for(int i = 0; i < 31; i++){
        struct data *curr = hashTables[i];
        while(curr){
            free(curr);
            curr = curr->next;
        }
        hashTables[i] = NULL;
    }
}

void init()
{
    for(int i = 0 ; i < 31 ; i++)
    {
        hashTables[i] = NULL;
    }
}

int main()
{
    char data[][100] =
    {
        "roti",
        "keju",
        "coklat",
        "durian",
        "nasi",
        "buncis",
        "ayam",
        "air",
        "mie",
        "tahu",
        "tempe",
        "susu",
        "sapi",
        "telur",
        "biskuit",
        "wortel",
        "steak",
        "kentang",
        "apel",
        "melon",
        "ikan"
    };
    init();
    int count = sizeof(data) / sizeof(data[0]);
    for(int i = 0 ; i < count ; i++)
    {
        int idx = hash(data[i]);
        if(strcmp(data[i], "tempe") == 0){
            printf("%d\n", idx);
        }
        chaining(idx,data[i]);
    }
    viewAll();
    popAll();
    viewAll();
    return 0;
}