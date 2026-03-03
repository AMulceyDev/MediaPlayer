#include <stdio.h>

struct
{
    char BusinessName[50];
    char BusinessAddress[100];
    char BusinessPhone[15];
    char BussinessIdentificationNumber[20]; //siret in France
    char BusinessEmail[50];
    char BillingDate[20];
    char BillingNumber[20];
} Header;

struct
{
    char legalNotice[200];
    char paymentTerms[100];
} Footer;

struct
{
    char name[50];
    char address[100];
} Customer;

struct
{
    char description[100];
    int quantity;
    float unitPrice;
    float totalPrice;
} Item;

struct
{
    char IBAN[34];
    char BIC[11];

} PaymentDetails;





f


int main(void) {
    printf("Hello, World!\n");
    return 0;
}