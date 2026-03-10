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




// Loading and generating config file functions
// --------------------------------------------------------------------
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

void generateConfigFile(Constants constants)
{
    printf("Generating configuration file...\n");
    FILE *file = fopen("config.txt", "w");
    if (file == NULL)
    {
        printf("Error creating configuration file.\n");
        return;
    }
    //constants = {};
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
    return ;
}

void loadConfigFile(Constants constants)
{
    printf("Loading configuration file...\n");
    FILE *file = fopen("config.txt", "r");
    if (file == NULL)
    {
        printf("Error opening configuration file.\n");
        return;
    }
    int verif = 0;
    //constants = {};
    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        char *key = strtok(line, "=");
        char *value = strtok(NULL, "\n");
        if (strcmp(key, "Business-Name") == 0)
        {
            strcpy(constants.BusinessName, value);
            verif++;
        }
        else if (strcmp(key, "Business-Address") == 0)
        {
            strcpy(constants.BusinessAddress, value);
            verif++;
        }
        else if (strcmp(key, "Business-Phone") == 0)
        {
            strcpy(constants.BusinessPhone, value);
            verif++;
        }
        else if (strcmp(key, "Bussiness-Identification-Number") == 0)
        {
            strcpy(constants.BussinessIdentificationNumber, value);
            verif++;
        }
        else if (strcmp(key, "Business-Email") == 0)
        {
            strcpy(constants.BusinessEmail, value);
            verif++;
        }
        else if (strcmp(key, "Legal-Notice") == 0)
        {
            strcpy(constants.legalNotice, value);
            verif++;
        }
        else if (strcmp(key, "Payment-Terms") == 0)
        {
            strcpy(constants.paymentTerms, value);
            verif++;
        }
        else if (strcmp(key, "IBAN") == 0)
        {
            strcpy(constants.IBAN, value);
            verif++;
        }
        else if (strcmp(key, "BIC") == 0)
        {
            strcpy(constants.BIC, value);
            verif++;
        }
    }
    fclose(file);
    if (verif != 9)
    {
        printf("Configuration file is invalid. Generating a new one...\n");
        generateConfigFile(constants);
        return ;
    }
    return ;
}




// Billing generation functions
// --------------------------------------------------------------------
Customer customerGathering()
{
    Customer customer = {};
    printf("%s", "Please enter the following information about the customer:\n");
    printf("Customer Name: ");
    scanf("%s", customer.name);
    printf("Customer Address: ");
    scanf("%s", customer.address);
    printf("Billing Date (dd/mm/yyyy): ");
    scanf("%s", customer.BillingDate);
    printf("Billing Number: ");
    scanf("%s", customer.BillingNumber);
    return customer;
}
Item itemGathering()
{
    Item item = {};
    printf("%s", "Please enter the following information about the item:\n");
    printf("Item Description: ");
    scanf("%s", item.description);
    printf("Item Quantity: ");
    scanf("%d", &item.quantity);
    printf("Item Unit Price: ");
    scanf("%f", &item.unitPrice);
    item.totalPrice = item.quantity * item.unitPrice;
    return item;
}
void billing(Constants constants)
{
    Customer customer = customerGathering();
    int itemCount = 0;
    Item *items = NULL;
    char choice = 'n';
    do
    {
        itemCount++;
        items = realloc(items, itemCount * sizeof(Item));
        items[itemCount - 1] = itemGathering();
        printf("Do you want to add another item? (y/n): ");
        printf("Your choice: ");
        scanf("%s", &choice);
        
    } while (choice == 'y' || choice == 'Y');
    
    

}

int main(void) {
    printf("Billing!\n");
    Constants constant;
    if (!isConfigFileValid())
    {
        generateConfigFile(constant);
    }
    else
    {
        loadConfigFile(constant);
    }
    billing(constant);
    return 0;
    
}