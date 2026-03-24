#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define NB_CARDS 52
#define NB_DECKS 6
#define MAX_HAND_CARDS 11

typedef struct Card {
    char name[30];
    int value;
} Card;

typedef struct Shoe {
    Card cards[NB_CARDS * NB_DECKS];
    int top;
} Shoe;

typedef struct Hand {
    Card cards[MAX_HAND_CARDS];
    int totalCards;
    int totalValue;
} Hand;

void generateShoe(Shoe *shoe) {
    char *suits[] = {"Spades", "Hearts", "Diamonds", "Clubs"};
    char *ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
    int   values[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};

    int i = 0;
    for (int deckIndex = 0; deckIndex < NB_DECKS; deckIndex++) {
        for (int suitIndex = 0; suitIndex < 4; suitIndex++) {
            for (int rankIndex = 0; rankIndex < 13; rankIndex++) {
                Card card;
                snprintf(card.name, 30, "%s of %s", ranks[rankIndex], suits[suitIndex]);
                card.value = values[rankIndex];
                shoe->cards[i] = card;
                i++;
            }
        }
    }

    shoe->top = 0;
    shuffleShoe(shoe);
}

void shuffleShoe(Shoe *shoe) {
    srand(time(NULL));
    int total = NB_CARDS * NB_DECKS;
    for (int i = total - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Card tmp = shoe->cards[i];
        shoe->cards[i] = shoe->cards[j];
        shoe->cards[j] = tmp;
    }
}

Card drawCard(Shoe *shoe, Hand *hand) {
    Card topCard = shoe->cards[shoe->top];
    shoe->top++;

    hand->cards[hand->totalCards] = topCard; 
    hand->totalCards++;
    hand->totalValue += topCard.value;

    return topCard;
}

void initGame(Shoe *shoe, Hand *playerHand, Hand *bankHand) {
    playerHand->totalValue = 0;
    playerHand->totalCards = 0;
    bankHand->totalValue = 0;
    bankHand->totalCards = 0;

    for (int i = 0; i < 2; i++) {
        drawCard(shoe, playerHand);
    }

    for (int i = 0; i < 2; i++) {
        drawCard(shoe, bankHand);
    }
}

void gameLogic(Shoe *shoe) {
    Hand playerHand;
    Hand bankHand;

    initGame(shoe, &playerHand, &bankHand);

    printf("Player card's (");
    for (int i = 0; i < playerHand.totalCards; i++) {
        printf("%s, ", playerHand.cards[i].name);
    }
    printf(") (Total visible: %d)\n", playerHand.totalValue);

    printf("Bank card's (1 hidden, %s) (Total visible: %d)\n",
           bankHand.cards[1].name, bankHand.cards[1].value);

    char choice[20];
    while (1) {
        printf("'stand' or 'draw' : ");
        scanf("%19s", choice);

        if (strcmp(choice, "stand") == 0 || strcmp(choice, "s") == 0) {
            break;

        } else if (strcmp(choice, "draw") == 0 || strcmp(choice, "d") == 0) {
            Card card = drawCard(shoe, &playerHand);
            printf("Player draws a %s (Total: %d)\n", card.name, playerHand.totalValue);

            if (playerHand.totalValue == 21) {
                printf("BlackJack ! Player Win !\n");
                return;
            } else if (playerHand.totalValue > 21) {
                printf("Bust ! Bank Win !\n");
                return;
            }

        } else if (strcmp(choice, "exit") == 0) {
            return;
        }
    }

    printf("\nBank turn\n");
    printf("Bank reveals: (");
    for (int i = 0; i < bankHand.totalCards; i++) {
        printf("%s, ", bankHand.cards[i].name);
    }
    printf(") (Total: %d)\n", bankHand.totalValue);

    while (bankHand.totalValue < 17) {
        Card card = drawCard(shoe, &bankHand);
        printf("Bank draws a %s (Total: %d)\n", card.name, bankHand.totalValue);

        if (bankHand.totalValue > 21) {
            printf("Bust ! Player Win !\n");
            return;
        }
    }

    printf("\nPlayer: %d | Bank: %d\n", playerHand.totalValue, bankHand.totalValue);
    if (playerHand.totalValue > bankHand.totalValue) {
        printf("Player Win !\n");
    } else if (playerHand.totalValue == bankHand.totalValue) {
        printf("Push !\n");
    } else {
        printf("Bank Win !\n");
    }
}

int main() {
    printf("BlackJack by Amaury Mulcey\n\n");

    Shoe shoe;
    generateShoe(&shoe);

    gameLogic(&shoe);

    return 0;
}