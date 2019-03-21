// Write a program that calls `fork()`. Before calling `fork()`, have the main process access a variable
// (e.g., x) and set its value to something (e.g., 100). What value is the variable in the child process?
// What happens to the variable when both the child and parent change the value of x?

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    int x = 100;

    // only ran once in "pre-Parent" process
    printf("Before Parent and Child, there was only Zuul.\n");

    int child = fork();

    if (!child)
    {
        // conditional to child process
        // doesn't see the variable assignment within the "parent block" though it happened already
        printf("Child says, \"x is %d.\"\n", x);
    }
    else if (child > 0)
    {
        // conditional to parent process
        // reassigns variable x, but child can't see that
        x = 44;
        printf("Parent says, \"x is %d.\"\n", x);
    }
    else
    {
        fprintf(stderr, "Fork failed\n");
        // only 0 is standard exit success
        exit(1);
    }

    return 0;
}
