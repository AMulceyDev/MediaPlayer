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

void sortBank(Coin bank[], int bankSize) {
    for (int i = 0; i < bankSize; i++) {
        for (int j = 0; j < bankSize - i - 1; j++) {
            if (bank[j].value < bank[j + 1].value) {
                Coin temp = bank[j];
                bank[j] = bank[j + 1];
                bank[j + 1] = temp;
            }
        }
    }
}

int computeChange(Coin bank[], int bankSize, int remaining, Coin result[], int index) {
    if (remaining == 0) return 1;
    if (index >= bankSize || remaining < 0) return 0;

    int maxCoins = remaining / bank[index].value;
    if (maxCoins > bank[index].number) {
        maxCoins = bank[index].number;
    }

    for (int use = maxCoins; use >= 0; use--) {
        result[index].number = use;
        if (computeChange(bank, bankSize, remaining - use * bank[index].value, result, index + 1)) {
            return 1;
        }
    }

    result[index].number = 0;
    return 0;
}

int main() {
    printf("Change calculator by Amaury Mulcey\n\n");

    Coin bank[8] = {
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

    sortBank(bank, bankSize);
    showBank(bank, bankSize);

    int value;
    do {
        printf("\nhow much to give back (-1 to exit) : ");
        scanf("%d", &value);

        if (value == -1) {
            break;
        }

        Coin result[bankSize];
        for (int i = 0; i < bankSize; i++) {
            result[i] = bank[i];
        }

        for (int i = 0; i < bankSize; i++) {
            result[i].number = 0;
        }

        int canChange = computeChange(bank, bankSize, value, result, 0);
        if (!canChange) {
            printf("Cannot give exact change with current coins\n");
        } else {
            for (int i = 0; i < bankSize; i++) {
                bank[i].number -= result[i].number;
            }
            showBank(bank, bankSize);
        }
    } while (value != -1);

    return 0;
}