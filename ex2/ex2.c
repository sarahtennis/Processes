// Write a program that opens the text.txt file (with the `fopen()` library call) located in this directory
// and then calls `fork()` to create a new process. Can both the child and parent access the file descriptor
// returned by `fopen()`? What happens when they are written to the file concurrently?

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    // open text.txt with fopen()
    FILE *filePtr;

    filePtr = fopen("text.txt", "w");

    // call fork() to create new process
    // if fork is before fopen(), child overwrites parent -- mode: w
    // otherwise file stays open until all processes finish (maybe can't close while active process accessing?)
    int child = fork();

    if (!child)
    {
        fprintf(filePtr, "Child says, \"The best PID is: %d\"\n", (int)getpid());
    }
    else if (child > 0)
    {
        fprintf(filePtr, "Parent says, \"The best PID is: %d, not %d.\"\n", (int)getpid(), child);
    }
    else
    {
        fprintf(stderr, "Fork failed.\n");
        exit(1);
    }

    fclose(filePtr);

    return 0;
}
