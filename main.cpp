#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h> 
#include<time.h> // OUTPUT CURRENT TIME
#include<sys/utsname.h> // OUTPUT OS

// LINKED LIST
struct Dish{
    char name[255];
    int price;
    int quantity;
    Dish *next, *prev;
}*head = NULL, *tail = NULL;

// g var
char dishOrder[255][255]; 
int dishOrderCount[255];
int price[255] = {};
int indexOrder;

Dish* createDish(const char* name, int price, int quantity){
    Dish* newDish = (Dish*) malloc (sizeof(Dish));
    strcpy(newDish->name, name);
    newDish->price = price;
    newDish->quantity = quantity;
    newDish->next = NULL;
    return newDish;
}

void pushHead(Dish* createDish){
    if(head == NULL){
        head = tail = createDish;
    } else {
        createDish->next = head;
        head->prev = createDish;
        head = createDish;
    }
}

void pushTail(Dish* createDish){
    if(head == NULL){
        head = tail = createDish;
    } else {
        tail->next = createDish;
        createDish->prev = tail;
        tail = createDish;
    }
}

void pushMid(Dish *createDish){
    if(head == NULL){
        head = tail = createDish;
    } 
    else if(createDish->quantity >= head->quantity){
        pushHead(createDish);
    }
    else if(createDish->quantity <= tail->quantity){
        pushTail(createDish);
    }
    else if(head->next == tail){
        head->next = createDish;
        createDish->prev = head;

        createDish->next = tail;
        tail->prev = createDish;
    }
    else {
        Dish *curr = head->next;
        while(curr->next != NULL){
            if(createDish->quantity <= curr->quantity && createDish->quantity > curr->next->quantity){
                break;
            }
            curr = curr->next;
        }
        Dish *afterCurr = curr->next;
        curr->next = createDish;
        createDish->prev = curr;

        createDish->next = afterCurr;
        afterCurr->prev = createDish;
    }
}

void popHead(){
    if(head == NULL){
        return;
    }
    else if(head == tail){
        free(head);
        head = tail = NULL;
    }
    else {
        Dish *curr = head;
        head = head->next;
        head->prev = curr->next = NULL; // delete arrow
        free(curr);
    }
}

void popTail(){
    if(head == NULL){
        return;
    }
    else if(head == tail){
        free(head);
        head = tail = NULL;
        
    }
    else {
        Dish *curr = tail->prev;
        curr->next = curr->prev = NULL;
        free(tail);
        tail = curr;
    }
}

void popMid(const char *name){
    if(head == NULL){
        return;
    } 
    else if(strcmp(head->name, name) == 0){
        popHead();
    }
    else if(strcmp(tail->name, name) == 0){
        popTail();
    }
    else {
        Dish *curr = head;
        while(curr->next != NULL){
            if(strcmp(curr->name, name) == 0){
                break;
            }
            curr = curr->next;
        }
        if(strcmp(curr->name, name) == 0){
            Dish *beforeCurr = curr->prev;
            Dish *afterCurr = curr->next;
            curr->prev = curr->next = NULL;
            free(curr);
            beforeCurr->next = afterCurr;
            afterCurr->prev = beforeCurr;
            return;
        }
    }
}

void display(){
    puts("                  Bude's Menu         ");
    puts("==============================================");
    if(head == NULL){
        puts("                    No Data");
    } else {
        Dish *curr = head;
        int idx = 1;
        puts("No.  Name                  Quantity   Price  ");
        while(curr != NULL){
            printf("%d.   %-20s  %-5.03d      Rp%d  \n", idx++, curr->name, curr->quantity, curr->price);
            curr = curr->next;
        }
    }

}

bool search(const char *name){
    if(head == NULL){
        return false;
    } else {
        Dish *curr = head;
        while(curr != NULL && strcmp(curr->name, name) != 0){
            curr = curr->next;
        }
        if(curr == NULL){
            return false;
        } else {
            return true;
        }
    }
}

bool searchOrder(const char *name){
    if(head == NULL){
        return false;
    } else {
        Dish *curr = head;
        while(curr != NULL && strcmp(curr->name, name) != 0){
            curr = curr->next;
        }
        if(curr == NULL){
            return false;
        } else {
            price[indexOrder] += curr->price;
            return true;
        }
    }
}


// HASH TABLE
const int SZ = 10;
struct Customer{
    char name[255];
    char menu[SZ][255];
    int count[SZ];
    Customer *next;
}*headCust[SZ], *tailCust[SZ];

Customer *createCustomer(const char *name){
    Customer *newCustomer = (Customer*) malloc(sizeof(Customer));
    strcpy(newCustomer->name, name);
    newCustomer->next = NULL;
    return newCustomer;
}

unsigned long djb2(const char *str){
    unsigned long key = 5381;
    for(int i = 0; str[i] != '\0'; i++){
        int ascii = int(str[i]);
        key = ((key << 5) + key) + ascii;
    }
    return key % SZ;
}

void insertCustomer(Customer *createCustomer){
    int idx = djb2(createCustomer->name);
    if(headCust[idx] == NULL){
        headCust[idx] = tailCust[idx] = createCustomer;
    } else {
        tailCust[idx]->next = createCustomer;
        tailCust[idx] = createCustomer;
    }
}

void traverseLL(int i){
    Customer *curr = headCust[i];
    while(curr){
        printf("%d. %s\n", i, curr->name);
        curr = curr->next;
    }
}

void displayCustomer(){
    for(int i = 0; i < SZ; i++){
        if(headCust[i]){
            traverseLL(i);
        } 
    }
}

bool findInside(int i, const char *query){
    Customer *curr = headCust[i];
    while(curr){
        if(strcmp(curr->name, query) == 0){
            return true;
        }
    }
    return false;
}

bool searchCustomer(const char *query){
    for(int i = 0; i < SZ; i++){
        if(headCust[i]){
            if(findInside(i, query) == true) return true;
        }
    }
    return false;
}

void findRemove(int i, const char *query, int *checker){
    Customer *curr = headCust[i];
    while(curr){
        if(strcmp(curr->next->name, query) == 0){
            Customer *beforeCurr = curr;
            curr = curr->next;
            Customer *afterCurr = curr;
            beforeCurr->next = afterCurr;
            free(curr);
            *checker = 1;
            return;
        }
    }
}

void customerRemove(const char *query){
    int checker = 0;
    for(int i = 0; i < SZ; i++){
        if(headCust[i]){
            findRemove(i, query, &checker);
            if(checker == 1) return;
        }
    }
}

// Main Prototype
int mainMenu();
void add();
void remove();
void addCust();
void searchCust();
void viewWarteg();
void order();
void payment();
void exitWarteg();

// Validate Prototype
bool checkLetter(const char* dishName);
bool checkCust(char name[]);
bool checkAvailable(const char *name);

// Utilize
void enter();
void clear();
void addData(const char *name, int price, int quantity);
void updateData();
void readFile();
void addCustomertoFile(const char *name);
void readCustomerFile();

int main(){
    int option;
    readFile();
    readCustomerFile();
    do{
        clear();
        option = mainMenu();
        switch(option){
            case 1: {
                add();
                break;
            }
            case 2: {
                remove();
                break;
            }
            case 3: {
                addCust();
                break;
            }
            case 4: {
                searchCust();
                break;
            }
            case 5: {
                viewWarteg();
                break;
            }
            case 6: {
                order();
                break;
            }
            case 7: {
                payment();
                break;
            }
            case 8: {
                exitWarteg();
                break;
            }
        }
    }while(option != 8);

    return 0;
}

int mainMenu(){
    clear();
    time_t clock;
	time(&clock);
    struct utsname system_os;
    uname(&system_os);	
	printf("System: %s\n", system_os.sysname);
    printf("%s\n", ctime(&clock));
    puts("1. Add Dish");
    puts("2. Remove Dish");
    puts("3. Add Customer");
    puts("4. Search Customer");
    puts("5. View Warteg");
    puts("6. Order");
    puts("7. Payment");
    puts("8. Exit Warteg");
    int option;
    do{
        printf(">> ");
        scanf("%d", &option); getchar();
    }while(option < 1 || option > 8);
    return option;
}

void add(){
    clear();
    char dishName[255];
    do{
        strcpy(dishName, "");
        printf("Insert the name of the dish [Lowercase letters, space is not allowed]: ");
        scanf("%s", dishName); getchar();
    }while(checkLetter(dishName) == true);

    int price;
    do{
        printf("Insert the price of the dish [1000..50000]: ");
        scanf("%d", &price); getchar();
    }while(price < 1000 || price > 50000);

    int quantity;
    do{
        printf("Insert the quantity of the dish [1..999]: ");
        scanf("%d", &quantity); getchar();
    }while(quantity < 1 || quantity > 999);
    pushMid(createDish(dishName, price, quantity));
    addData(dishName, price, quantity);
    puts("The dish has been added!");
    enter();
}

void remove(){
    clear();
    display();
    puts("==============================================");
    char name[255];
    do{
        strcpy(name, "");
        printf("Insert dish's name to be deleted ['cancel' to exit]: ");
        scanf("%[^\n]", name); getchar();
        if(strcmp(name, "cancel") == 0){
            break;
        }
        if(search(name) == false){
            printf("Dish not found\n");
        }
    }while(search(name) == false);
    if(strcmp(name, "cancel") != 0){
        popMid(name);
        puts("The dish has been removed!");
        enter();    
    }
    updateData();
}

void addCust(){
    clear();
    char name[255];
    do{
        strcpy(name, "");
        printf("Insert the customer's name [Without space]: ");
        scanf("%[^\n]", name); getchar();

    }while(checkCust(name) == true);
    insertCustomer(createCustomer(name));
    addCustomertoFile(name);
    puts("Customer has been added!");
    enter();
}

void searchCust(){
    clear();
    char nameSearch[255] = {};
    printf("Insert the customer's name to be searched: ");
    scanf("%[^\n]", nameSearch); getchar();
    bool found = searchCustomer(nameSearch);
    if(found == true) printf("%s is registered\n", nameSearch);
    else printf("%s is not registered\n", nameSearch);
    enter();
}

void viewWarteg(){
    clear();
    puts("Customer's List");
    displayCustomer();
    enter();
}

void order(){
    indexOrder = 0;
    clear();
    char name[255] = {};
    do{
        printf("Insert the customer's name: ");
        scanf("%[^\n]", name); getchar();
    }while(checkAvailable(name) == true);

    int n;
    printf("Insert the amount of dish: ");
    scanf("%d", &n); getchar();

    for(int i = 0; i < n; i++){
        int nominal;
        char dishName[255] = {};
        do{
            printf("[%d] Insert the dish's name and quantity: ", i+1);
            scanf("%s x%d", dishName, &nominal); getchar();
        }while(searchOrder(dishName) == false);
        
        strcpy(dishName, dishOrder[indexOrder]);
        
        dishOrderCount[indexOrder++];
    }
    puts("Order success");
    enter();
}

void payment(){
    clear();
    displayCustomer();
    int n;
    printf("Insert the customer's index: ");
    scanf("%d", &n); getchar();
    printf("%s\n", headCust[n]->name);
    for(int i = 0; i < indexOrder; i++){
        printf("[%d] %s\n", dishOrder, dishOrderCount);
    }
    printf("Total: Rp%d\n", price);
    customerRemove(headCust[n]->name);
    enter();
}

void exitWarteg(){
    clear();
    FILE *in = fopen("splash-screen.txt", "r");
    char splash[255] = {};
    while(!feof(in)){
        
        fscanf(in, "%[^\n]\n", splash);
        printf("%s\n", splash);
    }
    fclose(in);
    puts("Please expand your terminal to full screen!");
    enter();
}

bool checkLetter(const char* dishName){
    int len = strlen(dishName);
    for(int i = 0; i < len; i++){
        if(dishName[i] >= 'A' && dishName[i] <= 'Z'){
            return true;
        }
    }
    return false;
}

bool checkCust(char name[]){
    int len = strlen(name);
    for(int i = 0; i < len; i++){
        if(name[i] == ' '){
            return true;
        }
    }
    return false;
}

bool checkAvailable(const char *name){
    bool check = searchCustomer(name);
    if(check == true){
        return false;
    } else {
        return true;
    }
}

void enter(){
    fflush(stdin);
    puts("Press enter to continue...");
    char command;
    scanf("%c", &command);
}

void clear(){
    // system("cls");
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
    fflush(stdout);
}

void addData(const char *name, int price, int quantity){
    FILE *out = fopen("dish_list.txt", "a");
    fprintf(out, "%s#%d#%d\n", name, price, quantity);
    fclose(out);
}

void updateData(){
    FILE *out = fopen("dish_list.txt", "w");
    Dish *curr = head;
    while(curr != NULL){
        fprintf(out, "%s#%d#%d\n", curr->name, curr->price, curr->quantity);
        curr = curr->next;
    }
    fclose(out);
}

void readFile(){
    FILE *in = fopen("dish_list.txt", "r");
    char name[255];
    int price, quantity;
    while(!feof(in)){
        strcpy(name, "");
        fscanf(in, "%[^#]#%d#%d\n", name, &price, &quantity);
        pushTail(createDish(name, price, quantity));
    }
    fclose(in);
}

void addCustomertoFile(const char *name){
    FILE *out = fopen("customer_list.txt", "a");
    fprintf(out, "%s\n", name);
    fclose(out);
}

void readCustomerFile(){
    FILE *in = fopen("customer_list.txt", "r");
    char name[255];
    while(!feof(in)){
        strcpy(name, "");
        fscanf(in, "%[^\n]\n", name);
        insertCustomer(createCustomer(name));
    }
    fclose(in);
}