/*
Write a program that will find the average time it takes for your computer
to make a system call an empty write to stdout. Your program should use the 
`clock_gettime` procedure to time how long a single system call takes. It'll 
do this for one million iterations, and then find the average of all of those 
iterations in nanoseconds.
For some helpful documentation and examples of using time-related system calls,
visit this site: https://www.cs.rutgers.edu/~pxk/416/notes/c-tutorials/gettime.html
While the linked site does say that `clock_gettime()` does not work on OSX, this 
turns out to only be the case for OSX versions < 10.12. Anything later than that 
and `clock_gettime()` should work just fine. 
*/

/*
    struct timespec {
	    time_t   tv_sec; 
	    long     tv_nsec;
    }
*/

#include <stdio.h>
#include <unistd.h>
#include <time.h>

#define number_iter 1000000
#define BILLION 1000000000L

int main()
{
    long total = 0;
    long difference;

    for (int x = 0; x < number_iter; x++)
    {
        struct timespec start, end;

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);

        write(STDOUT_FILENO, "", 0);

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

        // convert seconds to nano, add nano
        difference = BILLION * ((long)end.tv_sec - (long)start.tv_sec) + (end.tv_nsec - start.tv_nsec);

        total += difference;
    }

    // print average in nanoseconds
    printf("Average time to execute empty write to stdout: %ld nsec\n", total / (long)number_iter);

    return 0;
}
