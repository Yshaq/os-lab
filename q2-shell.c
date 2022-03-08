#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>

FILE *fp;
char*filename; 

void createHistoryFile() {
    filename = strcat(getenv("HOME"), "/customShellHistory.txt");
    fp = fopen(filename, "w");
    fclose(fp);
}

void addToHistory(char *cmd) {
    char *token = strtok(cmd, "\t");
    if(strcmp(token, "\n")) {
        fp = fopen(filename, "a");
        fputs(cmd, fp);
        fclose(fp);
    }
}

void showHistory() {
    char *hist;
    fp = fopen(filename, "r");
    while(fgets(hist, 100, fp)) {
        printf("%s\n", hist);
    }
    fclose(fp);
}

int checkInput(char *cmd) {
    if (!strcmp(cmd, "exit")) {
        exit(0);
        return -1;
    }
    else if (!strcmp(cmd, "history")) {
        showHistory();
        return 1;
    }
    return 0;
}

char **parseCmd(char *cmd) {
    int i=0;
    char **tokens = malloc(101 * sizeof(char *));
    char *token;
    token = strtok(cmd, " \n\t");
    while(token != NULL) {
        tokens[i] = token;
        i++;
        token = strtok(NULL, " \n\t");
    }
    tokens[i] = NULL;
    return tokens;
}

int execute(char **cmd) {
    if (!strcmp(cmd[0], "cd") && cmd[1] != NULL) {
        if(chdir(cmd[1])) {
            printf("Invalid Path!\n");
        }
        return 1;
    }

    pid_t forked = fork();
    if (forked == 0) {
        if(execvp(cmd[0], cmd) == -1) {
            printf("Invalid command!!\n");
            exit(0);
        } 
        exit(0);
    }
    else if (forked < 0) printf("Fork Error\n");
    else wait(0);
    return 1;
}

void startShell() {
    printf("\n----Custom Shell Running----\n");
    createHistoryFile();
    while (1) {
        char input[100];
        char **parsedInput;
        char dir[100];
        getcwd(dir, sizeof(dir));
        printf("\n%s >>> ", dir);
        fgets(input, 100, stdin);
        if (input[strlen(input)-1] != '\n') {
            printf("Command length limit exceeded!\n");
            while(getchar()!='\n') continue;
            continue;
        }
        else {
            addToHistory(input);
            parsedInput = parseCmd(input);
            int f = checkInput(input);
            if (!f) {
                execute(parsedInput);
            };
        }
    }    
}

int main() {
    startShell();
    return 0;
}
