#include <stdio.h>

typedef struct Coin {
    char name[10];
    int value; // in centimes
    int number; // number of coins in bank
} Coin;

int main() {
    printf("Change calculator by Amaury Mulcey\n");

    Coin bank[15] = {
        {"1 centime", 1, 0},
        {"2 centime", 2, 0},
        {"5 centime", 5, 0},
        {"10 centime", 10, 0},
        {"20 centime", 20, 0},
        {"50 centime", 50, 0},
        {"1 euro", 100, 0},
        {"2 euros", 200, 0},

        {"5 euros", 500, 0},
        {"10 euros", 1000, 0},
        {"20 euros", 2000, 0},
        {"50 euros", 5000, 0},
        {"100 euros", 10000, 0},
        {"200 euros", 20000, 0},
        {"500 euros", 50000, 0}
    };

    printf("%s / %d / %d\n", bank[0].name, bank[0].value, bank[0].number);

    return 0;
}