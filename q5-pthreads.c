#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>

#define MAX_N 90

// this data is shared by the threads.
long int fib[MAX_N];

// thread func to compute fibonacci.
void *runner(void *param) {
    int *ptr = (int *)param;
    int n = *ptr;
	fib[0] = 0;
	fib[1] = 1;
	for (int i = 2; i < n; i++) {
		fib[i] = fib[i - 1] + fib[i - 2];
	}
	pthread_exit(0);
}

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

	pthread_t tid;
	pthread_attr_t attr;

	// init thread with default attributes.
	pthread_attr_init(&attr);

	// create the thread.
	pthread_create(&tid, &attr, runner, &n);
	
	// parent thread will wait for the child thread to exit.
	pthread_join(tid, NULL);
	
	// parent thread will output the fib sequence computed by the child thread.
	printf("Fibonacci sequence: ");
	for (int i = 0; i < n; i++) {
		printf("%ld ", fib[i]);
	}
	printf("\n");

	return 0;
}