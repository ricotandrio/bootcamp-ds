#include<stdio.h>
#include<stdlib.h>
// #include<conio.h>

struct wagonTrain{
    char cargoType;
    int cargoID;
    struct wagonTrain *next;
};

struct wagonTrain *pushCargo(struct wagonTrain *WT, char cargoType, int cargoID){
    struct wagonTrain *newCargo = (struct wagonTrain*)malloc(sizeof(struct wagonTrain));
    newCargo->cargoType = cargoType;
    newCargo->cargoID = cargoID;
    newCargo->next = NULL;
    if(WT == NULL){
        WT = newCargo;
    }
    else{
        struct wagonTrain *curr = WT;
        while(curr->next != NULL) curr = curr->next;
        curr->next = newCargo;
    }
    return WT;
}

void printWagonTrain(struct wagonTrain *WT){
    struct wagonTrain *curr = WT;
    while(curr != NULL){
        if(curr == WT)
            printf("%c%d", curr->cargoType, curr->cargoID);
        else if(curr->next == NULL)
            printf(" :: %c%d\n", curr->cargoType, curr->cargoID);
        else
            printf(" :: %c%d", curr->cargoType, curr->cargoID);
            curr = curr->next;
    }
}

void printAllTrainSet(struct wagonTrain *polarExpress, struct wagonTrain *bachmannPenn, struct wagonTrain *santaFe, struct wagonTrain*hogwartsExpress){
    printf("LIST OF TRAIN SET\n");
    printf("=================\n");
    printf("%-17s %s", "Polar Express", "= ");
    printWagonTrain(polarExpress);
    printf("%-17s %s", "Bachmann Penn", "= ");
    printWagonTrain(bachmannPenn);
    printf("%-17s %s", "Santa Fe", "= ");
    printWagonTrain(santaFe);
    printf("%-17s %s", "Hogwarts Express", "= ");
    printWagonTrain(hogwartsExpress);
}

// [#] INSERT YOUR CODE HERE, YOU NEED TO COMPLETE THIS FUNCTION WITH YOUR ANSWER
int checkWagonTrainCargo(struct wagonTrain *A, struct wagonTrain *B){
    int total = 0, same = 0, notSame = 0;
    struct wagonTrain *tempA = A;
    struct wagonTrain *tempB = B;

    while(tempA != NULL && tempB != NULL){
        total++;
        if(tempA->cargoID == tempB->cargoID && tempA->cargoType == tempB->cargoType){
            same++;
        } else {
            notSame++;
        }
        tempA = tempA->next;
        tempB = tempB->next;
    }
    if(total == same) return 1;
    else return 0;
}

int main(){
    int i = 0, j = 0;
    char cargoType[3] = {'A', 'B', 'C'};
    int cargoIDType[10] = {12, 23, 35, 47, 56, 66, 78, 84, 92};
    // TRAIN SET 1 - Polar Express
    struct wagonTrain *polarExpress = NULL;
    for(i=0 ; i<9 ; i++)
        polarExpress = pushCargo(polarExpress, cargoType[i%3],
        cargoIDType[i]);
    // TRAIN SET 2 = Bachmann Penn
    struct wagonTrain *bachmannPenn = NULL;
    for(i=0 ; i<9 ; i+=2)
        bachmannPenn = pushCargo(bachmannPenn, cargoType[i%3],
        cargoIDType[i]);
    for(j=1 ; j<9 ; j+=2)
        bachmannPenn = pushCargo(bachmannPenn, cargoType[j%3],
        cargoIDType[j]);

    // TRAIN SET 3 = Santa Fe
    struct wagonTrain *santaFe = NULL;
    for(i=8 ; i>=0 ; i--)
        santaFe = pushCargo(santaFe, cargoType[i%3],
        cargoIDType[i]);
    // TRAIN SET 4 = Hogwarts Express
    struct wagonTrain *hogwartsExpress = NULL;
    hogwartsExpress = pushCargo(hogwartsExpress, 'A', 12);
    hogwartsExpress = pushCargo(hogwartsExpress, 'B', 23);
    hogwartsExpress = pushCargo(hogwartsExpress, 'C', 35);
    for(i=3 ; i<9 ; i++)
        hogwartsExpress = pushCargo(hogwartsExpress,
        cargoType[i%3], cargoIDType[i]);
    // A FUNCTION TO SEE ALL TRAIN SET
    // printAllTrainSet(polarExpress, bachmannPenn, santaFe,hogwartsExpress);
    // POLAR EXPRESS & BACHMANN PENN
    printf("%d\n", checkWagonTrainCargo(polarExpress, bachmannPenn));
    // SANTA FE & HOGWARTS EXPRESS
    printf("%d\n", checkWagonTrainCargo(santaFe, hogwartsExpress));
    // HOGWARTS EXPRESS & POLAR EXPRESS
    printf("%d\n", checkWagonTrainCargo(polarExpress,hogwartsExpress));
    // getch();
    return (0);
}