#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int fork_count = 0;

void fork_recursive() {
    pid_t pid = fork();
    if (pid < 0) {
        // fork failed, report the last count
        printf("Number of successful forks: %d\n", fork_count);
        exit(1);
    } else if (pid == 0) {
        // child process, increment the count and fork again
        fork_count++;
        printf("Number of successful forks: %d\n", fork_count);
        fork_recursive();
    } else {
        // parent process, wait for child to finish
        wait(NULL);
    }
}

int main() {
    fork_recursive();
    return 0;
}

// this code will create a child process and parent process and print number of successful forks in both of them
// so  if you have other processes running in your system then you will get number of successful forks decreasing for each successful fork
// but you run only 1 fork process so you will get number of successful forks increasing for each successful fork