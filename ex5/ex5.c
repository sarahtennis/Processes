// Write a program that forks a child and creates a shared pipe
// between the parent and child processes. Have the child write
// the three messages to the parent and have the parent print out
// the messages.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MSGSIZE 16

char *msg1 = "hello world #1\n";
char *msg2 = "hello world #2\n";
char *msg3 = "hello world #3\n";

int main(void)
{
    int pipe_name[2];
    char buf[MSGSIZE * 3];

    pipe(pipe_name);

    pid_t child = fork();

    if (child == 0)
    // child block
    {
        int written1 = write(pipe_name[1], msg1, MSGSIZE);
        int written2 = write(pipe_name[1], msg2, MSGSIZE);
        int written3 = write(pipe_name[1], msg3, MSGSIZE);

        if (written1 == -1 || written2 == -1 || written3 == -1)
        {
            perror("write");
            exit(1);
        }
    }
    else if (child > 0)
    {
        // parent block
        wait(NULL);

        int read_int = read(pipe_name[0], buf, sizeof(buf));

        write(STDOUT_FILENO, buf, read_int);
    }
    else
    {
        fprintf(stderr, "Fork failed.\n");
        exit(1);
    }

    return 0;
}
