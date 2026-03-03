#include <stdio.h>

typedef struct Coin {
    char name[12];
    int value; // in centimes
    int number; // number of coins in bank
} Coin;

void showBank(Coin bank[], int bankSize) {
    printf("\nSummary of the bank\n");
    for (int i = 0; i < bankSize; i++) {
        printf("- %d coins of %s\n", bank[i].number, bank[i].name);
    }
}

int main() {
    printf("Change calculator by Amaury Mulcey\n\n");

    Coin bank[] = {
        {"1 centime", 1, 0},
        {"2 centimes", 2, 0},
        {"5 centimes", 5, 0},
        {"10 centimes", 10, 0},
        {"20 centimes", 20, 0},
        {"50 centimes", 50, 0},
        {"1 euro", 100, 0},
        {"2 euros", 200, 0},
    };

    int bankSize = sizeof(bank) / sizeof(bank[0]);
    for (int i = 0; i < bankSize; i++) {
        printf("how many %s do you have? : ", bank[i].name);
        scanf("%d", &bank[i].number);
    }

    showBank(bank, bankSize);

    int value;
    do {
        printf("\nhow much to give back (-1 to exit) : ");
        scanf("%d", &value);

        if (value == -1) {
            continue;
        }

        showBank(bank, bankSize);
    }
    while (value != -1);
    
    return 0;
}