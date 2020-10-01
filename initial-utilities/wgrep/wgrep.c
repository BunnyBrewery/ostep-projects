#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    if (argc == 1) {
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }
    
    char* sTerm = argv[1];
    if (argc == 2) {
        char buffer[1000];
        while(fgets(buffer, 1000, stdin) != NULL) {
            char* line = strstr(buffer, sTerm);
            if (line != NULL) {
                printf("%s", buffer);
            }
        }
        return 0;
    }

    for (int i = 2; i < argc; i++) {
        char* fname = argv[i];
        FILE *fp = fopen(fname, "r");
        if (fp == NULL) {
            printf("wgrep: cannot open file\n");
            exit(1);
        }
        size_t limit = 1000;
        char *buffer = (char *)malloc(1000 * sizeof(char));
        while(1) {
            int ret = getline(&buffer, &limit, fp);
            if (ret == -1) {
                break;
            }
            char* line = strstr(buffer, sTerm);
            if (line != NULL) {
                printf("%s", buffer);
            }
        }

    }
}
