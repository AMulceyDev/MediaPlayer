#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
    char BusinessName[50];
    char BusinessAddress[100];
    char BusinessPhone[15];
    char BussinessIdentificationNumber[20]; //siret in France
    char BusinessEmail[50];
    char BillingDate[20];
    char BillingNumber[20];
} Header;

typedef struct
{
    char legalNotice[200];
    char paymentTerms[100];
} Footer;

typedef struct
{
    char name[50];
    char address[100];
} Customer;

typedef struct
{
    char description[100];
    int quantity;
    float unitPrice;
    float totalPrice;
} Item;

typedef struct
{
    char IBAN[34];
    char BIC[11];

} PaymentDetails;





bool isConfigFileValid()
{
    FILE *file = fopen("config.txt", "r");
    if (file == NULL)
    {
        return false;
    }
    fclose(file);
    return true;
}

void generateConfigFile()
{
    FILE *file = fopen("config.txt", "w");
    if (file == NULL)
    {
        printf("Error creating configuration file.\n");
        return;
    }
    Header header = {};
    printf("Enter Business Name: ");
    scanf("%s", header.BusinessName);

    printf("Enter Business Address: ");
    scanf("%s", header.BusinessAddress);

    printf("Enter Business Phone (format: +0000000000): ");
    scanf("%s", header.BusinessPhone);

    printf("Enter Business Identification Number (SIRET in France): ");
    scanf("%s", header.BussinessIdentificationNumber);

    printf("Enter Business Email: ");
    scanf("%s", header.BusinessEmail);


    fprintf(file, "[Header]\n");
    fprintf(file, "BusinessName=%s\n", header.BusinessName);
    fprintf(file, "BusinessAddress=%s\n", header.BusinessAddress);
    fprintf(file, "BusinessPhone=%s\n", header.BusinessPhone);
    fprintf(file, "BussinessIdentificationNumber=%s\n", header.BussinessIdentificationNumber);
    fprintf(file, "BusinessEmail=%s\n", header.BusinessEmail);
    fclose(file);
}


int main(void) {
    if (!isConfigFileValid())
    {
        generateConfigFile();
    }
    
}