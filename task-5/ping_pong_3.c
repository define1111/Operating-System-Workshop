#define _POSIX_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

enum { success_exit = 0, fork_err, read_err, arg_err };

struct ball
{
    __int32_t begin;
    __int32_t end;
    __int32_t current;
};

typedef struct ball ball_t;

int pipefd_ping_pong[2];

void end_game_handler(int signum)
{
    close(pipefd_ping_pong[0]);
    close(pipefd_ping_pong[1]);
    exit(success_exit);
}

void check_read(int fd, void *buf, size_t count)
{
    if (read(fd, buf, count) != count)
    {
        perror("read");
        exit(read_err);
    }
}

int main(int argc, char **argv)
{
    pid_t child1, child2, child3;
    int pipefd[2];    
    ball_t ball;

    if (argc != 3)
    {
        fprintf(stderr, "usage: ./pp3 <begin> <end>\n");
        return arg_err;
    }

    ball.begin = atoi(argv[1]);
    ball.end = atoi(argv[2]);
    ball.current = ball.begin;

    if (ball.begin >= ball.end)
    {
        fprintf(stderr, "end must be greater then begin\n");
        return arg_err;
    }
  
    pipe(pipefd);
    pipe(pipefd_ping_pong);

    child1 = fork();
    if (child1 == -1)
    {
        perror("fork child1");
        exit(fork_err);
    }    

    if (child1 == 0)
    {
        signal(SIGTERM, end_game_handler);
        raise(SIGSTOP);
        close(pipefd[1]);
        check_read(pipefd[0], &child2, sizeof(pid_t));
        kill(child2, SIGCONT);
        check_read(pipefd[0], &child3, sizeof(pid_t));
        close(pipefd[0]);

        for (;;)
        {
            if (ball.begin != ball.current) raise(SIGSTOP);
            if (ball.begin != ball.current) check_read(pipefd_ping_pong[0], &ball, sizeof(ball_t));
            if (ball.current >= ball.end) break;
            ball.current++;
            fprintf(stdout, "child1: %d\n", ball.current);
            write(pipefd_ping_pong[1], &ball, sizeof(ball_t));
            kill(child2, SIGCONT);
        }

        kill(child2, SIGCONT);
        kill(child2, SIGTERM);

        kill(child3, SIGCONT);
        kill(child3, SIGTERM);
    
        close(pipefd_ping_pong[0]);
        close(pipefd_ping_pong[1]);

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
        signal(SIGTERM, end_game_handler);
        raise(SIGSTOP);
        check_read(pipefd[0], &child3, sizeof(pid_t));
        child2 = getpid();
        write(pipefd[1], &child2, sizeof(pid_t));
        kill(child1, SIGCONT);
        raise(SIGSTOP);
        close(pipefd[0]);
        write(pipefd[1], &child3, sizeof(pid_t));
        close(pipefd[1]);

        for (;;)
        {
            raise(SIGSTOP);
            check_read(pipefd_ping_pong[0], &ball, sizeof(ball_t));
            if (ball.current >= ball.end) break;
            ball.current++;
            fprintf(stdout, "child2: %d\n", ball.current);
            write(pipefd_ping_pong[1], &ball, sizeof(ball_t));
            kill(child3, SIGCONT);
        }
        

        kill(child1, SIGCONT);
        kill(child1, SIGTERM);

        kill(child3, SIGCONT);
        kill(child3, SIGTERM); 

        close(pipefd_ping_pong[0]);
        close(pipefd_ping_pong[1]);
        
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
        signal(SIGTERM, end_game_handler);
        close(pipefd[0]);
        child3 = getpid();
        write(pipefd[1], &child3, sizeof(pid_t));
        close(pipefd[1]);
        kill(child2, SIGCONT);

        for (;;)
        {
            raise(SIGSTOP);
            check_read(pipefd_ping_pong[0], &ball, sizeof(ball_t));
            if (ball.current >= ball.end) break;
            ball.current++;
            fprintf(stdout, "child3: %d\n", ball.current);
            write(pipefd_ping_pong[1], &ball, sizeof(ball_t));
            kill(child1, SIGCONT);
        } 
     
        kill(child1, SIGCONT);
        kill(child1, SIGTERM);

        kill(child2, SIGCONT);
        kill(child2, SIGTERM); 
        
        close(pipefd_ping_pong[0]);
        close(pipefd_ping_pong[1]);
                
        return success_exit;
 }
   
    close(pipefd_ping_pong[0]);
    close(pipefd_ping_pong[1]);

    close(pipefd[0]);
    close(pipefd[1]);

    wait(NULL);
    wait(NULL);
    wait(NULL);
    return success_exit;
}


