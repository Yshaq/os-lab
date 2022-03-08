#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t baseId = getpid();
    printf("Base ID: %d\n", baseId);
    int level = 0;

    for (int i=0; i<4; i++) {
        pid_t newFork = fork();
        if(newFork == 0) {
            pid_t parentId = getppid();
            pid_t processId = getpid();
            level++;
            printf("This is a child process (%d, lvl %d) of parent process %d\n", processId, level, parentId);
        }
        else if(newFork>0) {
            wait(0);
        }
        else {
            printf("Fork Error!");
        }
    }


    return 0;
}