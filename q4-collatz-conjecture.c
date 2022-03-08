#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

//collatz conjecture, do n/2 if even, 3n+1 if odd. eventually should reach 1
int main() {

    int n;

    while(1) {
        printf("Enter starting number: ");
        scanf("%d", &n);

        if (n < 0) {
            printf("Only postive integers allowed!\n");
            continue;
        }
        break;
    }

    pid_t child = fork();
    if (child < 0) {
        printf("Fork Error!");
        exit(EXIT_FAILURE);
    }
    else if (child > 0) {
        //run the collatz conjecture till 1
        while(1) {
            printf("%d ", n);

            if(n==1) break;

            if (n%2 == 0) n/=2;
            else n = 3*n + 1;

        }
    }
    else {
        wait(0);
        printf("\nparent done waiting");
    }


    return 0;
}