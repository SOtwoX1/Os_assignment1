#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    printf("hello world (pid: %d)\n",(int) getpid());
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("hello, I am child (pid: %d)\n",(int) getpid());
        printf("Child's parent process ID: %d\n", getppid());
        // child exits immediately
    } else {
        // parent goes down this path (original process)
        sleep(5); // parent sleeps for 5 seconds
        printf("hello, I am parent of %d (pid: %d)\n", rc, (int) getpid());
    }
    return 0;
}
// this code will create a child process and parent process and print hello world in both of them
// sleep() is used to sleep for 5 seconds in parent process and print hello, I am parent in parent process
// child will exit immediately in parent process because parent process is sleeping for 5 seconds