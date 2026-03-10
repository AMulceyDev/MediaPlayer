#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int loadFromCSV(Coin bank[], int bankSize) {
    FILE *file = fopen("data.csv", "r");

    if (!file) {
        return 0;
    }

    char line[256];
    char last_line[256];
    while (fgets(line, sizeof(line), file)) {
        strcpy(last_line, line);
    }

    char *strToken = strtok(last_line, ",");

    for (int i = 0; i < bankSize; i++) {
        bank[i].number = atoi(strToken);
        strToken = strtok ( NULL, "," );
    }
    fclose(file);

    return 1;
}

void updateCSVFile(Coin bank[], int bankSize) {
    FILE *file = fopen("data.csv", "a");
    fprintf(file, "%d,%d,%d,%d,%d,%d,%d,%d\n", bank[0].number, bank[1].number, bank[2].number, bank[3].number, bank[4].number, bank[5].number, bank[6].number, bank[7].number);
    fclose(file);
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
        {"1 cent", 1, 0},
        {"2 cents", 2, 0},
        {"5 cents", 5, 0},
        {"10 cents", 10, 0},
        {"20 cents", 20, 0},
        {"50 cents", 50, 0},
        {"1 euro", 100, 0},
        {"2 euros", 200, 0},
    };

    int bankSize = sizeof(bank) / sizeof(bank[0]);
    int isBankLoaded = loadFromCSV(bank, bankSize);

    if (!isBankLoaded) {
        for (int i = 0; i < bankSize; i++) {
            printf("How many %s do you have? : ", bank[i].name);
            scanf("%d", &bank[i].number);
        }
    }

    showBank(bank, bankSize);
    sortBank(bank, bankSize);
    if (!isBankLoaded) {
        updateCSVFile(bank, bankSize);
    }

    int value;
    do {
        printf("\nHow much change to give back (in cents)? (-1 to exit) :");
        scanf("%d", &value);

        if (value == -1) {
            break;
        }

        Coin result[bankSize];
        for (int i = 0; i < bankSize; i++) {
            result[i] = bank[i];
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
            updateCSVFile(bank, bankSize);
        }
    } while (value != -1);

    return 0;
}