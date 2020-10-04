#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void initInteractiveShell();
void initBatchShell(char* batchFile);
void changeDirectory(char* buffer, int length, int max); 
void parseArgs(char* buffer, int* length, int* max, char* args);

int main(int argc, char** argv) {
    if (argc > 2) {
        return 1; // error
    } else if (argc == 1) {
        // interactive mode
        initInteractiveShell();
    } else if (argc == 2) {
        // batch mode
        char* fileName = argv[1];
        initBatchShell(fileName);
    } else {
        return 0;
    }
    return 0;
}

void initInteractiveShell() {
    while (1) {
        fprintf(stdout, "wish> ");
        char* buffer = (char*) malloc(20 * sizeof(char));
        size_t limit = 20;
        int len  = getline(&buffer, &limit, stdin);
        if (len == -1) {
            break;
        }
        if (buffer[len-1] == '\n') {
            buffer[len-1] = '\0';
        }
        char* cmd;
        cmd = strsep(&buffer, " ");
        int length = 0, max = 0;
        char*  args = strdup("keke");
        if (buffer == NULL) {
            args = NULL;
        } else {
            parseArgs(buffer, &length, &max, args);
        }
        int result;
        if ((result = strcmp(cmd, "exit")) == 0) {
            exit(0);
        } else if ((result = strcmp(cmd, "cd")) == 0) {
            printf("cd entered\n");
            changeDirectory(args, length, max);
        } else if ((result = strcmp(cmd, "path")) == 0) {
            printf("path entered\n");
        } else {
            //execv
        }
        /*
        while ((token = strsep(&buffer, " ")) != NULL) {
            
        }
        */
    }
}

void initBatchShell(char* batchFile) {
    ;
}



void changeDirectory(char* args, int length, int max) {
    if (length != 1) {
        printf("error: only 1 arguement\n");
        return;
    }
    printf("this: %s\n", args);
}

void parseArgs(char* buffer, int* length, int* max, char* args) {
    //int len = (int) strlen(buffer);
    char temp[1000] = "";
    strcpy(temp, buffer);
    char* token;
    int count = 0, maxLen = 0;
    char* gg = temp;
    while((token = strsep(&gg, " ")) != NULL) {
        count++;
        int len = strlen(token);
        if (len > maxLen) {
            maxLen = len;
        }
    }
    if (count == 0) {
        return;
    }
    char hehe[count][maxLen];
    int i = 0;
    while((token = strsep(&buffer, " ")) != NULL) {
        strcpy(hehe[i], token);
        i++;
    }
    *length = count;
    args = (char*) hehe;
    
}
