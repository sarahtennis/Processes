// Write a program that calls `fork()` and then calls some form of `exec()`
// to run the program `/bin/ls`. Try a few variants of `exec()`, such as
// `execl()`, `execle()`, `execv()`, and others. Why do you think there
// are so many variants of the same basic call?

/*
    The exec...() functions load and execute a new program, known as a
    child process.

    All eight of the exec...() functions perform the same operation; they
    differ only in how arguments are passed, the use of the DOS PATH in
    searching for the program to be run ('pathname'), and the use of the
    DOS environment.

    'l': arguments to child passed as list
    'v': arguments to child passed as array (when # of arguments isn't known in advance, first usually 'pathname', last must be NULL pointer)
    'p': search using DOS PATH environment variable
    'e': allow calling program to alter called program's environment by passing a list of environment settings in the envp arg

    execl, execlp, execv, execvp: allow child process to inherit calling program's environment
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>

int main(void)
{
    pid_t pid = fork();

    if (pid == 0)
    // child block
    {
        execlp("ls", "ls", NULL);
    }
    else if (pid > 0)
    {
        // parent block
        wait(NULL);
        execl("ls", "ls", NULL);

        if (errno == ENOENT)
            printf("ls not found in current directory\n");
        else if (errno == ENOMEM)
            printf("not enough memory to execute ls\n");
        else
            printf("  error #%d trying to exec ls\n", errno);

        exit(0);
    }
    else
    {
        fprintf(stderr, "Fork failed.\n");
        exit(1);
    }

    return 0;
}
