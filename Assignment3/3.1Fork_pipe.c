#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe failed");
        return -1;
    }

    int rc = fork();
    if (rc < 0) {
        // fork failed; exit 
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("Child (pid: %d)\n",(int) getpid());

        // close the read-end of the pipe
        close(fd[0]);

        // send a message through the pipe
        char message[100];
        sprintf(message, "Hello from %d", getpid());
        ssize_t bytes_written = write(fd[1], message, strlen(message)); // write() returns the number of bytes written
        if (bytes_written == -1) { // -1 indicates an error
            perror("write failed");
        }

        // close the write-end of the pipe
        close(fd[1]);
    } else {
        // parent goes down this path (original process)
        printf("Parent of %d (pid: %d)\n", rc, (int) getpid());

        // close the write-end of the pipe
        close(fd[1]);

        // read from the pipe
        char buffer[128];
        ssize_t bytes_read = read(fd[0], buffer, sizeof(buffer)); // read() returns the number of bytes read
        if (bytes_read == -1) { // -1 indicates an error
            perror("read failed");
        }

        // print the received message
        printf("Received message: %s\n", buffer);

        // close the read-end of the pipe
        close(fd[0]);
    }

    return 0;
}
// this code will create a child process and parent process and print hello world in both of them
// with pipe we can communicate between parent and child process
// read() is used to read from pipe and write() is used to write to pipe received message come from child process
// so parent process will print message in child process