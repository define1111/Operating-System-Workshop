#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>

enum { success_exit = 0, write_err, argc_err, open_err };
enum { key_size = 7 };

void check_write(int fd, const void *buf, size_t count)
{
    if (write(fd, buf, count) != count)
    {
        perror("write");
        exit(write_err);
    } 
}

void write_matrix(int fd, u_int64_t size)
{
    char *key = "MATRIX";
    u_int64_t i = 0;
    double current_number = 0.0;
  
    check_write(fd, key, key_size - 1);
    check_write(fd, &size, sizeof(u_int64_t));
 
    for (; i < size * size; i++)
    {
        current_number = (double) i + 1.0;
        check_write(fd, &current_number, sizeof(double)); 
    }
} 

int main(int argc, char **argv)
{
    int fd = -1;
    u_int64_t size = 0;
 
    if (argc != 3)
    {
        fprintf(stderr,  "usage: ./write_matrix <path> <size>\n");
        return argc_err;
    }  

    fd = open(argv[1], O_WRONLY | O_CREAT, 0600);
    if (fd == -1)
    {
        perror("open");
        return open_err;        
    } 

    size = atoi(argv[2]);
    write_matrix(fd, size);
    
    check_write(fd, &size, sizeof(u_int64_t));

    close(fd);
    return success_exit;
}
