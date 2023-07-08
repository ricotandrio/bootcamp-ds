#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>

struct Planet {
	long long int thermal;
	char name[35];
	int balanceFactor;
	int height;
	Planet *left, *right;
} *baseRoot = NULL;

int databaseCounter = 0;

struct Planet *createPlanet(long long int thermal, char *name){
	struct Planet *newPlanet = (struct Planet *) malloc (sizeof(struct Planet));
	newPlanet->thermal = thermal;
	strcpy(newPlanet->name, name);
	newPlanet->balanceFactor = 0;
	newPlanet->height = 1;
	newPlanet->left = newPlanet->right = NULL;	
	return newPlanet;
}

int maxValue(long long int a, long long int b){
    return (a >= b ? a : b);
}

int getHeight(struct Planet *root){
    return (!root ? 0 : root->height);
}

int getBalanceFactor(struct Planet *root){
    return getHeight(root->left) - getHeight(root->right);
}

int setHeight(struct Planet *root){
    return maxValue(getHeight(root->left), getHeight(root->right)) + 1;
}

Planet *updatePlanet(struct Planet *root){
    root->height = setHeight(root);
    root->balanceFactor = getBalanceFactor(root);
    return root;
}

Planet *leftRotate(struct Planet *root){
    Planet *pivot = root->right, *temp = root->left;
    pivot->left = root;
    root->right = temp;
    root = updatePlanet(root);
    pivot = updatePlanet(pivot);
    return pivot;
}

struct Planet *rightRotate(struct Planet *root){
    Planet *pivot = root->left, *temp = pivot->right;
    pivot->right = root;
    root->left = temp;
    root = updatePlanet(root);
    pivot = updatePlanet(pivot);
    return pivot;
}

struct Planet *rotate(struct Planet *root){
    if(root->balanceFactor > 1){
        if(root->left->balanceFactor >= 0){
            return rightRotate(root);
        } else {
            root->left = rightRotate(root);
        }
    } else if(root->balanceFactor < -1){
        if(root->right->balanceFactor <= 0){
            return leftRotate(root);
        } else {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }
    return root;
}

struct Planet *insert(struct Planet *root, struct Planet *newPlanet){
    if(!root) return newPlanet;
    else if(newPlanet->thermal < root->thermal) root->left = insert(root->left, newPlanet);
    else if(newPlanet->thermal >= root->thermal) root->right = insert(root->right, newPlanet);
    return rotate(updatePlanet(root));
}

struct Planet *predecessor(struct Planet *root){ 
    Planet *curr = root->left;
    while(curr->right) curr = curr->right;
    return curr;
}

struct Planet *remove(struct Planet *root, long long int thermal, bool foundStatus){
    if(!root) return root;
    else if(thermal < root->thermal) root->left = remove(root->left, thermal, foundStatus);
    else if(thermal > root->thermal) root->right = remove(root->right, thermal, foundStatus);
    else {
    	if(foundStatus == false){
    		foundStatus = true;
    		databaseCounter--;
		}
        if(!root->left || !root->right){
            Planet *newRoot = root->left ? root->left : root->right;
            root->left = root->right = NULL;
            free(root);
            root = NULL;
            return newRoot;
        }
        Planet *inOrderPredecessor = predecessor(root);
        root->thermal = inOrderPredecessor->thermal;
        root->left = remove(root->left, inOrderPredecessor->thermal, foundStatus);
    }
    return root;
}
 
void inOrderDisplay(struct Planet *root, long long int from, long long int to, int *counter){
	if(root){
		if(root->left) inOrderDisplay(root->left, from, to, counter);
	    (*counter)++;
		if(root && *counter >= from && *counter <= to) printf("  %lld: %lld %s\n", *counter, root->thermal, root->name);
		if(root->right) inOrderDisplay(root->right, from, to, counter);
	}
}
	
void searchingForInterval(struct Planet *root, long long int thermal, bool found){
	if(root && found == false){
		if(root->left) searchingForInterval(root->left, thermal, found);
		if(root->thermal == thermal){
			printf("  (0) %lld %s\n", root->thermal, root->name); 
			found = true; 
			return;
		} else if(root->left && root->right && root->thermal != thermal){
			int a, b, c;
			a = abs(root->thermal - thermal);
			b = abs(root->right->thermal - thermal);
			c = abs(root->left->thermal - thermal);
			if(a <= b && a <= c){
				printf("  (1) %lld %s\n", root->thermal, root->name);
				found = true; 
				return;	
			} else if(b <= a && b <= c){
				printf("  (2) %lld %s\n", root->right->thermal, root->right->name);
				found = true; 
				return;
			} else { 
				printf("  (3) %lld %s\n", root->left->thermal, root->left->name);
				found = true; 
				return;
			}
		} else if(root->left || root->right){
			struct Planet *existPlanet = root->right ? root->right : root->left;
			if(abs(root->thermal - thermal) > abs(existPlanet->thermal - thermal)){
				printf("  (4) %lld %s\n", existPlanet->thermal, existPlanet->name);
				found = true; 
				return;
			} else {
				printf("  (5) %lld %s\n", root->thermal, root->name);
				found = true; 
				return;
			}
		} 
		if(root->right) searchingForInterval(root->right, thermal, found);
	}
}

bool validateCommand(char *str, int len);
void getCommand();

int getLargerThermal(struct Planet *root, long long int thermal, int counter);
void mainmenuMessage();

void clear();
void enter();

int main(){
	// Test Case dari Soal
//	baseRoot = createPlanet(1500, "mars");
//	databaseCounter++;
//	printf("  Number of planet/asteroid that has larger thermal: %d\n", getLargerThermal(baseRoot, 1500, 0));
//	
//	insert(baseRoot, createPlanet(1000, "proxima"));
//	databaseCounter++;
//	printf("  Number of planet/asteroid that has larger thermal: %d\n", getLargerThermal(baseRoot, 1000, 0));
//		
//	insert(baseRoot, createPlanet(2500, "venus"));
//	databaseCounter++;
//	printf("  Number of planet/asteroid that has larger thermal: %d\n", getLargerThermal(baseRoot, 2500, 0));
//
//	searchingForInterval(baseRoot, 1000, false);
//	
//	insert(baseRoot, createPlanet(3900, "jupiter"));
//	databaseCounter++;
//	printf("  Number of planet/asteroid that has larger thermal: %d\n", getLargerThermal(baseRoot, 3900, 0));
//	
//	remove(baseRoot, 1500, false);
//	printf("  Number of planet/asteroid exists in the database: %d\n", databaseCounter);
//	
//	int temp = 0;
//	inOrderDisplay(baseRoot, 1, 10, &temp);
//	
//	searchingForInterval(baseRoot, 5000, false);
//	
//	remove(baseRoot, 1200, false);
//	printf("  Number of planet/asteroid exists in the database: %d\n", databaseCounter);
//	
//	insert(baseRoot, createPlanet(1000, "centaur"));
//	databaseCounter++;
//	printf("  Number of planet/asteroid that has larger thermal: %d\n", getLargerThermal(baseRoot, 1000, 0));
	
	int total;
	printf("\n  TEST CASE > ");
	scanf("%d", &total);
	for(int i = 0; i < total; i++){
		mainmenuMessage();
		getCommand();
	}
	return 0;
}

void mainmenuMessage(){
	clear();
	puts("\n  << BeeAero Database System >>\n\n");
	puts("  i.   INSERT NEW PLANETS/ASTEROIDS");
	puts("  ii.  DELETE PLANETS/ASTEROIDS");
	puts("  iii. FIND SIMILAR PLANETS/ASTEROIDS");
	puts("  iv.  SHOW PLANETS/ASTEROIDS");
	puts("\n\n  command form: \"1 <<thermal-temperature>> <<planet-name>>\"");
}

int getLargerThermal(struct Planet *root, long long int thermal, int counter){
	if(root){
        if(root->left) getLargerThermal(root->left, thermal, counter);
        if(root->thermal > thermal) counter++;
        if(root->right) getLargerThermal(root->right, thermal, counter);
    }	
    return counter;
}

void getCommand(){
	fflush(stdin);
	bool validate;
	do{
		char str[50] = {};
		printf("  >> ");
		scanf("%[^\n]", str); getchar();	
		validate = validateCommand(str, strlen(str));
	}while(validate == false);
}

bool validateCommand(char *str, int len){
	if(str[1] != ' ') return false;
	int commandNumber = str[0] - '0';
	if(commandNumber < 1 || commandNumber > 4) return false;
	int whiteSpaces = 0;
	for(int i = 0; i < len; i++){
		if(str[i] == ' ') whiteSpaces++;
		if(commandNumber == 1 && ((str[i] >= 'A' && str[i] <= 'Z') || whiteSpaces > 2)) return false;
		if((commandNumber == 2 || commandNumber == 3) && (whiteSpaces > 1 || (!(str[i] >= '0' && str[i] <= '9') && str[i] != ' '))) return false;
		if(commandNumber == 4 && (whiteSpaces > 2 || (!(str[i] >= '0' && str[i] <= '9') && str[i] != ' '))) return false;
	}
	
	long long int thermal, option, from, to;
	char name[35] = {};
	switch(commandNumber){
		case 1:
			sscanf(str, "%lld %lld %[^\0]", &option, &thermal, name);
			if(strlen(name) > 30 || whiteSpaces != 2) return false;
//			printf("%lld %lld %s\n", option, thermal, name);
			
			if(!baseRoot) baseRoot = createPlanet(thermal, name);
			else insert(baseRoot, createPlanet(thermal, name));
			
			databaseCounter++;
			printf("  Number of planet/asteroid that has larger thermal: %d\n", getLargerThermal(baseRoot, thermal, 0));
			break;
		case 2:
			sscanf(str, "%lld %lld", &option, &thermal);
//			printf("%lld %lld\n", option, thermal);
			
			if(!baseRoot) puts("  [!] there's no planet/asteroid exists in the database");
			else remove(baseRoot, thermal, false);
			
			printf("  Number of planet/asteroid exists in the database: %d\n", databaseCounter);
			break;
		case 3:
			sscanf(str, "%lld %lld", &option, &thermal);
//			printf("%lld %lld\n", option, thermal);
			
			searchingForInterval(baseRoot, thermal, false);
			break;
		case 4:
			sscanf(str, "%lld %lld %lld", &option, &from, &to);
			if(whiteSpaces != 2) return false;
//			printf("%lld, %lld, %lld\n", option, from, to, 0);
			int temp = 0;
			inOrderDisplay(baseRoot, from, to, &temp);
			break;
	}
	
	enter();
	return true;
} 

void clear(){
	fflush(stdin);
	system("cls");
//	for(int i = 0; i < 32; i++) puts("");
}

void enter(){
	fflush(stdin);
	puts("\n  press ENTER to continue ... ");
	printf("  "); getchar();
}
