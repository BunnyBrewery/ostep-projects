#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initInteractiveShell();
void initBatchShell(char* batchFile);
void changeDirectory(char* buffer); 
void updatePath(char* buffer);

char error_message[30] = "An error has occurred\n";
char PATH[100][100];

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
        int result;
        if ((result = strcmp(cmd, "exit")) == 0) {
            exit(0);
        } else if ((result = strcmp(cmd, "cd")) == 0) {
            changeDirectory(buffer);
        } else if ((result = strcmp(cmd, "path")) == 0) {
            updatePath(buffer);
        } else {
            int rc = fork();
            if (rc < 0) {
                write(STDERR_FILENO, error_message, strlen(error_message)); 
                exit(0);
            } else if (rc == 0) {
                printf("child\n")si
                char argv[100][100];
                char* token;
                int i = 0;
                printf("child 2 \n");
                while((token = strsep(&buffer, " ")) != NULL) {
                    printf("inside before\n");
                    strcpy(argv[i], token);
                    printf("inside after\n");
                    i++;
                }
                printf("i is: %d\n", i);
                printf("child 3 \n");
                argv[i][0] = '\0';
                printf("mahalo\n");
                for(int k = 0; k < i; k++) {
                   printf("argv %d: %s\n", k, argv[k]);
                }

                execv(cmd, argv);
            } else {
                printf("before waiting\n");
                wait(NULL);
                printf("after waiting\n");
            }
            
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

void updatePath(char* args) {
    char* token;
    int i = 0;
    while ((token = strsep(&args, " ")) != NULL) {
        strcpy(PATH[i], token);
        i++;
    }
   //strcpy(PATH[i], '\0');
   PATH[i][0] = '\0';
    for(int k = 0; k < i; k++ ) {
        printf("path %d: %s\n", k, PATH[k]);
    }
}

void changeDirectory(char* args) {
    if (args == NULL) {
        write(STDERR_FILENO, error_message, strlen(error_message)); 
        return;
    }
    char* path = strsep(&args, " ");
    if (args != NULL) {
        write(STDERR_FILENO, error_message, strlen(error_message)); 
        return;
    }
    int err = chdir(path);
    if (err == -1) {
        write(STDERR_FILENO, error_message, strlen(error_message)); 
    }
}

