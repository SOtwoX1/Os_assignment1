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
        printf("hello, I am parent of %d (pid: %d)\n", rc, (int) getpid());
    }
    return 0;
}
// this code will create a child process and parent process and print hello world in both of them
// if you run this code you will get hello world in parent process and hello, I am child in child process
// in both of them process id will be different but in parent process it will be same as in child process
// but in child process it will be different from parent process