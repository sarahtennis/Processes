// Write another program using `fork()`. The child process should print "hello";
// the parent process should print "goodbye". You should ensure that the child
// process always prints first.

/* pid_t waitpid(pid_t pid, int *status_ptr, int options);

pid_t pid
    Specifies the child processes the caller wants to wait for:
        If pid is greater than 0, waitpid() waits for termination of the specific child whose process ID is equal to pid.
        If pid is equal to zero, waitpid() waits for termination of any child whose process group ID is equal to that of the caller.
        If pid is -1, waitpid() waits for any child process to end.
        If pid is less than -1, waitpid() waits for the termination of any child whose process group ID is equal to the absolute value of pid.
int *status_ptr
    Points to a location where waitpid() can store a status value. This status value is zero if the child process explicitly returns zero status. Otherwise, it is a value that can be analyzed with the status analysis macros described in “Status Analysis Macros”, below.
    The status_ptr pointer may also be NULL, in which case waitpid() ignores the child's return status.

int options
    Specifies additional information for waitpid(). The options value is constructed from the bitwise inclusive-OR of zero or more of flags defined in the sys/wait.h header file
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    // fork new child process
    int child = fork();

    if (!child)
    {
        // child prints hello first, due to wait in parent block
        printf("Hello! (pid: %d)\n", (int)getpid());
    }
    else if (child > 0)
    {
        // waits until child process finishes
        int wait = waitpid(child, NULL, 0);
        printf("Had to wait on %d. Goodbye! (pid: %d)\n", wait, (int)getpid());
    }
    else
    {
        fprintf(stderr, "Fork failed.\n");
        exit(1);
    }
    return 0;
}
