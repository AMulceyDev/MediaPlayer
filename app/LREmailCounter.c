#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char user[100];
    char profil[100];
    printf("Which user?: \n");
    scanf("%s", user);
    printf("student or professor (s/p)?: \n");
    scanf("%s", profil);
    if (strcmp(profil, "s") == 0) {
        strcpy(profil, "etudiant");
    } else if (strcmp(profil, "p") == 0) {
        strcpy(profil, "enseignant");
    } else {
        printf("Invalid profile. Please enter 'e' or 'p'.\n");
        return 1;
    }
    char cmd[512];
    sprintf(
        cmd,
        "curl -s -X POST \"https://entfront.univ-lr.fr/php/wsBM.php\" -d \"uid=%s&profil=%s\"",
        user,
        profil);
    return system(cmd);
}