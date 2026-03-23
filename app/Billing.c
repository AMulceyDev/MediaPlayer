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

void readLine(char *buffer, size_t size)
{
    char format[32];
    if (size == 0)
    {
        return;
    }
    snprintf(format, sizeof(format), " %%%zu[^\n]", size - 1);
    if (scanf(format, buffer) != 1)
    {
        buffer[0] = '\0';
    }
    while (getchar() != '\n' && !feof(stdin))
        ;
}

void printInFile(FILE *file, char *text, char *args, size_t size, char *defaultValue)
{
    printf("%s, default(%s): ", text, defaultValue);
    readLine(args, size);
    if (strcmp(args, "/") == 0)
    {
        strcpy(args, defaultValue);
    }
    fprintf(file, "%s=%s\n", text, args);
}

void generateConfigFile(Constants *constants)
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
    printInFile(file, "Business-Name", constants->BusinessName, sizeof(constants->BusinessName), "Default Business Name");
    printInFile(file, "Business-Address", constants->BusinessAddress, sizeof(constants->BusinessAddress), "17000, La Rochelle, France");
    printInFile(file, "Business-Phone", constants->BusinessPhone, sizeof(constants->BusinessPhone), "0000000000");
    printInFile(file, "Bussiness-Identification-Number", constants->BussinessIdentificationNumber, sizeof(constants->BussinessIdentificationNumber), "00000000000000");
    printInFile(file, "Business-Email", constants->BusinessEmail, sizeof(constants->BusinessEmail), "default@example.com");
    printInFile(file, "Legal-Notice", constants->legalNotice, sizeof(constants->legalNotice), "Dispensé d’immatriculation au registre du commerce et des sociétés et au répertoire des métiers");
    printInFile(file, "Payment-Terms", constants->paymentTerms, sizeof(constants->paymentTerms), "TVA non applicable, art. 293 B du CGI");
    printInFile(file, "IBAN", constants->IBAN, sizeof(constants->IBAN), "000000000000000000000000000");
    printInFile(file, "BIC", constants->BIC, sizeof(constants->BIC), "000000000");
    fclose(file);
    return ;
}

void loadConfigFile(Constants *constants)
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
            strcpy(constants->BusinessName, value);
            verif++;
        }
        else if (strcmp(key, "Business-Address") == 0)
        {
            strcpy(constants->BusinessAddress, value);
            verif++;
        }
        else if (strcmp(key, "Business-Phone") == 0)
        {
            strcpy(constants->BusinessPhone, value);
            verif++;
        }
        else if (strcmp(key, "Bussiness-Identification-Number") == 0)
        {
            strcpy(constants->BussinessIdentificationNumber, value);
            verif++;
        }
        else if (strcmp(key, "Business-Email") == 0)
        {
            strcpy(constants->BusinessEmail, value);
            verif++;
        }
        else if (strcmp(key, "Legal-Notice") == 0)
        {
            strcpy(constants->legalNotice, value);
            verif++;
        }
        else if (strcmp(key, "Payment-Terms") == 0)
        {
            strcpy(constants->paymentTerms, value);
            verif++;
        }
        else if (strcmp(key, "IBAN") == 0)
        {
            strcpy(constants->IBAN, value);
            verif++;
        }
        else if (strcmp(key, "BIC") == 0)
        {
            strcpy(constants->BIC, value);
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
void customerGathering(Customer *customer)
{
    printf("%s", "Please enter the following information about the customer:\n");
    printf("Customer Name: ");
    readLine(customer->name, sizeof(customer->name));
    printf("Customer Address: ");
    readLine(customer->address, sizeof(customer->address));
    printf("Billing Date (dd/mm/yyyy): ");
    readLine(customer->BillingDate, sizeof(customer->BillingDate));
    printf("Billing Number: ");
    readLine(customer->BillingNumber, sizeof(customer->BillingNumber));
    return ;
}
void itemGathering(Item *item)
{
    printf("%s", "Please enter the following information about the item:\n");
    printf("Item Description: ");
    readLine(item->description, sizeof(item->description));
    printf("Item Quantity: ");
    while (scanf("%d", &item->quantity) != 1)
    {
        //while getchar car lors d'un bug, scanf ne supprime pas le caractère invalide de l'entrée, ce qui crée une boucle infinie
        // si le while n'est pas là, les charactère sont vidé un par un du buffeur mais l'affichage de invalid input se fait * le nom de char
        while (getchar() != '\n');
        printf("Invalid input. Item Quantity: ");
    }
    printf("Item Unit Price: ");
    while (scanf("%f", &item->unitPrice) != 1)
    {
        while (getchar() != '\n');
        printf("Invalid input. Item Unit Price: ");
    }
    //item.totalPrice = item.quantity * item.unitPrice;
    return ;
}
void billing(Constants *constants, Customer *customer, Item **items, int *itemCount)
{
    (void)constants;
    customerGathering(customer);
    char choice = 'n';
    do
    {
        (*itemCount)++;
        *items = realloc(*items, (*itemCount) * sizeof(Item));
        itemGathering(&(*items)[(*itemCount) - 1]);
        printf("%s", "Do you want to add another item? (y/n): ");
        scanf(" %c", &choice);
        
    } while (choice == 'y' || choice == 'Y');
    
    

}

void generateMarkdown(Constants constants, Customer customer, Item *items, int itemCount)
{
    FILE *file = fopen("invoice.md", "w");
    if (file == NULL)
    {
        printf("Error creating invoice file.\n");
        return;
    }
    fprintf(file, "# Invoice\n\n");
    fprintf(file, "## Business Information\n");
    fprintf(file, "- Name: %s\n", constants.BusinessName);
    fprintf(file, "- Address: %s\n", constants.BusinessAddress);
    fprintf(file, "- Phone: %s\n", constants.BusinessPhone);
    fprintf(file, "- Identification Number: %s\n", constants.BussinessIdentificationNumber);
    fprintf(file, "- Email: %s\n", constants.BusinessEmail);
    fprintf(file, "\n## Customer Information\n");
    fprintf(file, "- Name: %s\n", customer.name);
    fprintf(file, "- Address: %s\n", customer.address);
    fprintf(file, "- Billing Date: %s\n", customer.BillingDate);
    fprintf(file, "- Billing Number: %s\n", customer.BillingNumber);
    fprintf(file, "\n## Items\n");
    fprintf(file, "| Designation | Unit Price (EUR) | Quantity | Amount (EUR) |\n");
    fprintf(file, "| --- | ---: | ---: | ---: |\n");
    float totalAmount = 0;
    for (int i = 0; i < itemCount; i++)
    {
        items[i].totalPrice = items[i].quantity * items[i].unitPrice;
        totalAmount += items[i].totalPrice;
        fprintf(file, "| %s | %.2f | %d | %.2f |\n", items[i].description, items[i].unitPrice, items[i].quantity, items[i].totalPrice);
    }
    fprintf(file, "\n## Total Amount Due: %.2f\n", totalAmount);
    fprintf(file, "\n## Payment Terms\n");
    fprintf(file, "%s\n", constants.paymentTerms);
    fprintf(file, "- IBAN: %s\n", constants.IBAN);
    fprintf(file, "- BIC: %s\n", constants.BIC);
    fprintf(file, "\n## Legal Notice\n");
    fprintf(file, "%s\n", constants.legalNotice);
    fclose(file);
}

int main(void) {
    printf("Billing!\n");
    Constants constant = {0};
    Customer customer = {0};
    int itemCount = 0;
    Item *items = NULL;
    if (!isConfigFileValid())
    {
        generateConfigFile(&constant);
    }
    else
    {
        loadConfigFile(&constant);
    }
    billing(&constant, &customer, &items, &itemCount);
    generateMarkdown(constant, customer, items, itemCount);
    free(items);
    return 0;
    
}