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
    char legalNotice[200];
    char paymentTerms[100];
    char IBAN[34];
    char BIC[11];
} Constants;


typedef struct
{
    char name[50];
    char address[100];
    char BillingDate[20];
    char BillingNumber[20];
} Customer;

typedef struct
{
    char description[100];
    int quantity;
    float unitPrice;
    float totalPrice;
} Item;






bool isConfigFileValid()
{
    FILE *file = fopen("config.txt", "r");
    char line[256];
    if (file == NULL || !fgets(line, sizeof(line), file))
    {
        return false;
    }
    fclose(file);
    return true;
}

void printInFile(FILE *file, char *text, void *args, char *defaultValue)
{
    printf("%s, default(%s): ", text, defaultValue);
    scanf("%s", args);
    if (strcmp((char *)args, "/") == 0)
    {
        strcpy((char *)args, defaultValue);
    }
    fprintf(file, "%s=%s\n", text, (char *)args);
}

Constants generateConfigFile()
{
    FILE *file = fopen("config.txt", "w");
    if (file == NULL)
    {
        printf("Error creating configuration file.\n");
        return;
    }
    Constants constants = {};
    printf("%s", "Please enter the following information to generate the configuration file (/ to default):\n");
    printInFile(file, "Business-Name", constants.BusinessName, "Default Business Name");
    printInFile(file, "Business-Address", constants.BusinessAddress, "17000, La Rochelle, France");
    printInFile(file, "Business-Phone", constants.BusinessPhone, "0000000000");
    printInFile(file, "Bussiness-Identification-Number", constants.BussinessIdentificationNumber, "00000000000000");
    printInFile(file, "Business-Email", constants.BusinessEmail, "default@example.com");
    printInFile(file, "Legal-Notice", constants.legalNotice, "Dispensé d’immatriculation au registre du commerce et des sociétés et au répertoire des métiers");
    printInFile(file, "Payment-Terms", constants.paymentTerms, "TVA non applicable, art. 293 B du CGI");
    printInFile(file, "IBAN", constants.IBAN, "000000000000000000000000000");
    printInFile(file, "BIC", constants.BIC, "000000000");
    fclose(file);
    return constants;
}



int main(void) {
    if (!isConfigFileValid())
    {
        generateConfigFile();
    }
    
}