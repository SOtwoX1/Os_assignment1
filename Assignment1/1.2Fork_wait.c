#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int 
main(int argc, char *argv[]) 
{
    printf("hello world (pid: %d)\n",(int) getpid());
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("hello, I am child (pid: %d)\n",(int) getpid());
    } else {
        // parent goes down this path (original process)
        // add wait() for child process
        int wc = wait(NULL);
        printf("hello, I am parent of %d (wc:%d)(pid: %d)\n", rc, wc, (int) getpid());
    }
    return 0;
}
// this code will create a child process and parent process and print hello world in both of them
// if you run this code you will get hello world in parent process and hello, I am child in child process
// wait() is used to wait for child process to finish its execution and print hello, I am parent of 1 in parent process