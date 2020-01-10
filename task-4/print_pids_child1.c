#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    pid_t father, child1;

    father = getpid();
    
    child1 = fork();
    if (child1 == -1)
    {
        perror("fork child1");
        exit(1);
    }    

    if (child1 == 0)
    {
        fprintf(stdout, "child1: father's pid = %d, child1's pid = %d\n", father, getpid());
        return 0;
    }

    fprintf(stdout, "father: father's pid = %d, child1's pid = %d\n", father, child1);

    wait(NULL);
    return 0;
}


