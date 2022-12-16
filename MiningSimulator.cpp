#include<stdio.h>
#include<stdlib.h>

struct Node{
    int cave;
    int gold;
    Node *left, *right;
}*baseRoot = NULL;

Node *createNode(int cave, int gold){
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->cave = cave;
    newNode->gold = gold;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node *insertNode(Node *root, int cave, int gold){
    if(!root){
        return createNode(cave, gold);
    }
    else if(cave < root->cave){
        root->left = insertNode(root->left, cave, gold);
    }
    else if(cave > root->cave){
        root->right = insertNode(root->right, cave, gold);
    }
    return root;
}

Node *searchNode(Node *root, int cave){
    if(!root || root->cave == cave){
        return root;
    }
    else if(cave < root->cave){
        return searchNode(root->left, cave);
    }
    else if(cave > root->cave){
        return searchNode(root->right, cave);
    }
}

void display(Node *root, int depth){
    if(root){
        display(root->left, depth+1);
        printf(">> Cave %03d  (depth %03d), total gold production: %d\n", root->cave, depth, root->gold);      
        display(root->right, depth+1);
        
    }
}

void reportMenu3(Node *root, int depth, int sum[]){
    if(root){
        sum[depth] = sum[depth] + root->gold;
        reportMenu3(root->left, depth+1, sum);
        reportMenu3(root->right, depth+1, sum);
    }
}

// prototype
void enter();
void clear();
int mainMenu();
void menu1();
void menu2();
void menu3();

int main(){
    int check;
    do{
        check = mainMenu();
        switch(check) {
            case 1: {
                menu1();
                break;
            }
            case 2: {
                menu2();
                break;
            }
            case 3: {
                menu3();
                break;
            }
            case 4: {
                puts("THANKS FOR USING HOV MINING SIMULATOR");
                break;
            }
        }
    }while(check != 4);

    return 0;
}

int mainMenu(){
    clear();
    puts("");
    puts("Hov Mining Simulator");
    puts("====================");
    puts("[1]. Insert Mining Data");
    puts("[2]. Display All Cave Data"); 
    puts("[3]. Display Mining Reports");
    puts("[4]. Exit");
    int input;
    do{
        printf(">> ");
        scanf("%d", &input); getchar();
    }while(input < 1 || input > 4);
    return input;
}

void menu1(){
    clear();
    int caveIndex;
    do{
        printf("Input cave index [1-999]\t: ");
        scanf("%d", &caveIndex); getchar();
    }while(caveIndex < 1 || caveIndex > 999);

    int goldProduction;
    do{
        printf("Input gold production [1-100]\t: ");
        scanf("%d", &goldProduction); getchar();
    }while(goldProduction < 1 || goldProduction > 100);
    Node *check = searchNode(baseRoot, caveIndex);
    if(!check){
        puts("New cave index detected.");
        printf("Total gold production for cave %d is %d\n\n", caveIndex, goldProduction);
    } else {
         puts("Cave index already exists.");
         printf("New total gold production for cave %d is %d\n\n", caveIndex, check->gold);
    }
    if(!baseRoot){
        baseRoot = insertNode(baseRoot, caveIndex, goldProduction);
    } else {
        insertNode(baseRoot, caveIndex, goldProduction);
    }
    enter();
}

void menu2(){
    clear(); 
    if(baseRoot){
        display(baseRoot, 1);
        puts("");    
    } else {
        puts("Cave data is empty, nothing to display\n");
    }
    
    enter();
}

void menu3(){
    clear(); 
    int sum[100] = {};
    if(baseRoot){
       reportMenu3(baseRoot, 1, sum);
        for(int i = 1; sum[i] != 0; i++){
            printf("Total gold production for depth %d is %d\n", i, sum[i]);
        }
    } else {
        puts("Cave data is empty, nothing to report\n");
    }
    
    enter();
}

void clear(){
    // system("cls");
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
    fflush(stdout);
}

void enter(){
    // getch not available in linux system
    fflush(stdin);
    puts("Press ENTER to continue...");
    char command;
    scanf("%c", &command);
}

