#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv) {
    if (argc == 1) {
        return 0;
    }
    FILE *fp;
    for (int i = 1; i < argc; i++) {
        char* fname = argv[i];
        fp = fopen(fname, "r");
        if (fp == NULL) {
            printf("wcat: cannot open file\n");
            exit(1);
        }
        int limit = 10000;
        char buffer[limit];
        while (fgets(buffer, limit, fp) != NULL) {
            printf("%s", buffer);
        }
        fclose(fp);
    }
    return 0;
}

