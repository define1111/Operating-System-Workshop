#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

enum { success_exit = 0, fork_err, read_err };
int main()
{
    pid_t father, child1, child2;
    int pipefd[2];    

    father = getpid();
    
    pipe(pipefd);

    child1 = fork();
    if (child1 == -1)
    {
        perror("fork child1");
        exit(fork_err);
    }    

    if (child1 == 0)
    {
        ssize_t rc = 0;

        close(pipefd[1]);
        rc =  read(pipefd[0], &child2, sizeof(pid_t));
        if (rc != sizeof(pid_t))
        {
            perror("read");
            exit(read_err);
        }
        fprintf(stdout, "child1: father's pid = %d, child1's pid = %d, child2's pid = %d\n", father, getpid(), child2);
        close(pipefd[0]);
        return success_exit;
    }
    
    child2 = fork();
    if (child2 == -1)
    {
        perror("fork child2");
        exit(fork_err);
    }

    if (child2 == 0)
    {
        close(pipefd[0]);
        child2 = getpid();
        write(pipefd[1], &child2, sizeof(pid_t));
        fprintf(stdout, "child2: father's pid = %d, child1's pid = %d, child2's pid = %d\n", father, child1, child2);
        close(pipefd[1]);
        return success_exit;
    }

    fprintf(stdout, "father: father's pid = %d, child1's pid = %d, child2's pid = %d\n", father, child1, child2);

    close(pipefd[0]);
    close(pipefd[1]);

    wait(NULL);
    wait(NULL);
    return success_exit;
}


