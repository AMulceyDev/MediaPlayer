#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int compressFile(const char* filePath) {
    printf("Compressing file: %s\n", filePath);
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filePath);
        return -1;
    }
    FILE *compressedFile = fopen("compressed_temp_file.txt", "w");
    if (compressedFile == NULL) {
        printf("Error opening compressed file.\n");
        fclose(file);
        return -1;
    }
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    long halfSize = fileSize / 2;
    fseek(file, halfSize, SEEK_SET);
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file))
    {
        fprintf(compressedFile, "%s", buffer);
    }
    fclose(compressedFile);
    if (remove(filePath) != 0) {
        printf("Error deleting original file: %s\n", filePath);
        return -1;
    }
    if (rename("compressed_temp_file.txt", filePath) != 0) {
        printf("Error renaming compressed file.\n");
        return -1;
    }
    fclose(file);
    return 0;
}


int main(void) {
    printf("Compress File!\n");
    char filePath[256];
    printf("Enter the path of the file to compress: ");
    scanf("%255s", filePath);
    if (compressFile(filePath) == 0) {
        printf("File compressed successfully.\n");
    } else {
        printf("Failed to compress the file.\n");
    }
}