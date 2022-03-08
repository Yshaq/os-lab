#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <ctype.h>

//collatz conjecture, do n/2 if even, 3n+1 if odd. eventually should reach 1
int main(int argc, char* argv[]) {

    if(argc != 2) {
        printf("exactly one parameter (integer) required\n");
        return 0;
    }

    char* s = argv[1];
    for(int i=0; s[i]!='\0'; i++) {
        if(!isdigit(s[i])) {
            printf("Please enter valid positive integer\n");
            return 0;
        }
    }

    int n = atoi(s);


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
        printf("\nparent done waiting\n");
    }


    return 0;
}