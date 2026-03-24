#include <stdio.h>
#include <string.h>

void encrypt(char *message, char *encryptedMessage, int rank) {
    for (int charIndex = 0; charIndex < strlen(message); charIndex++) {
        encryptedMessage[charIndex] = message[charIndex] + rank;
    }
    encryptedMessage[strlen(message)] = '\0';
}

int main() {
    printf("Text Encryption by Amaury Mulcey\n\n");

    char message[256];
    printf("Message to encrypt: ");
    scanf("%255s", message);

    int rank;
    printf("How much shift: ");
    scanf("%d", &rank);

    char encryptedMessage[256];
    encrypt(message, encryptedMessage, rank);
    printf("Encrypted: %s\n", encryptedMessage);

    return 0;
}