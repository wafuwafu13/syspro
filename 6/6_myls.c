#include <stdio.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    DIR *dir;
    struct dirent *de;

    dir = opendir(argv[1]);

    while ((de = readdir(dir)) != NULL) {
        printf("%lu %s\n", de->d_ino, de->d_name);
    }
    closedir(dir);
    return 0;
}
