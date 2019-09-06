#define _POSIX_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

enum { success_exit = 0, fork_err, read_err };

void check_read(int fd, void *buf, size_t count)
{
    if (read(fd, buf, count) != count)
    {
        perror("read");
        exit(read_err);
    }
}

int main()
{
    pid_t father, child1, child2, child3;
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
        raise(SIGSTOP);
        close(pipefd[1]);
        check_read(pipefd[0], &child2, sizeof(pid_t));
        kill(child2, SIGCONT);
        check_read(pipefd[0], &child3, sizeof(pid_t));
        fprintf(stdout, "child1: father's pid = %d, child1's pid = %d, child2's pid = %d, child3's pid = %d\n", father, getpid(), child2, child3);
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
        raise(SIGSTOP);
        check_read(pipefd[0], &child3, sizeof(pid_t));
        child2 = getpid();
        write(pipefd[1], &child2, sizeof(pid_t));
        fprintf(stdout, "child2: father's pid = %d, child1's pid = %d, child2's pid = %d, child3's pid = %d\n", father, child1, child2, child3);
        kill(child1, SIGCONT);
        raise(SIGSTOP);
        close(pipefd[0]);
        write(pipefd[1], &child3, sizeof(pid_t));
        close(pipefd[1]);
        return success_exit;
    }

    child3 = fork();
    if (child3 == -1)
    {
        perror("fork child3");
        exit(fork_err);
    }

    if (child3 == 0)
    {
        close(pipefd[0]);
        child3 = getpid();
        write(pipefd[1], &child3, sizeof(pid_t));
        fprintf(stdout, "child3: father's pid = %d, child1's pid = %d, child2's pid = %d, child3's pid = %d\n", father, child1, child2, child3);
        close(pipefd[1]);
        kill(child2, SIGCONT);
        return success_exit;
    }
   
    fprintf(stdout, "father: father's pid = %d, child1's pid = %d, child2's pid = %d, child3's pid = %d\n", father, child1, child2, child3);

    close(pipefd[0]);
    close(pipefd[1]);

    wait(NULL);
    wait(NULL);
    wait(NULL);
    return success_exit;
}


