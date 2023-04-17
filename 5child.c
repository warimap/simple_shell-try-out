#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int status;
    pid_t pid;

    // Create 5 child processes
    for (int i = 0; i < 5; i++) {
        pid = fork();
        if (pid == -1) {
            perror("fork failed");
            exit(1);
        } else if (pid == 0) {
            // Child process
            printf("Child %d executing ls -l /tmp\n", getpid());
            execl("/bin/ls", "ls", "-l", "/tmp", NULL);
            perror("execl failed");
            exit(1);
        } else {
            // Parent process
            wait(&status);
            printf("Child %d exited with status %d\n", pid, status);
        }
    }

    return (0);
}
