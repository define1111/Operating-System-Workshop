#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

enum { success_exit = 0, read_err, argc_err, open_err, wrong_matrix_format_err, alloc_err, lseek_err };
enum { key_size = 7 };

void check_read(int fd, void *buf, size_t count)
{
    if (read(fd, buf, count) != count)
    {
        perror("read");
        exit(read_err);
    }
}

void check_lseek(int fd, off_t offset, int whence)
{
    if (lseek(fd, offset, whence) == (off_t) -1)
    {
        perror("lseek");
        exit(lseek_err);
    }
}

u_int64_t check_correct_format_matrix(int fd)
{
    char *key = "MATRIX";
    char read_key[key_size];
    u_int64_t size = 0;
    
    read_key[key_size - 1] = '\0';
    check_read(fd, read_key, key_size - 1); 
    
    if (strncmp(key, read_key, key_size))
    {
        fprintf(stderr, "this file is not matrix\n");
        exit(wrong_matrix_format_err);
    }
    
    check_read(fd, &size, sizeof(u_int64_t));
    
    return size;
}

double summ_diag_matrix(int fd, u_int64_t size)
{
    double sum = 0.0, current_number = 0.0;
    u_int64_t i = 1;
    
    check_read(fd, &current_number, sizeof(double));
    fprintf(stdout, "%lf ", current_number);
    sum = current_number;

    for (; i < size; i++)
    {
        check_lseek(fd, size * sizeof(double), SEEK_CUR);
        check_read(fd, &current_number, sizeof(double));
        fprintf(stdout, "%lf ", current_number);
        sum += current_number;
    } 
    
    return sum;
}

int main(int argc, char **argv)
{  
    int fd = -1;
    u_int64_t size = 0;
    double sum = 0;
    
    if (argc != 2)
    {
        fprintf(stderr, "usage: ./read_matrix <path>\n");
        return argc_err;
    }
    
    fd = open(argv[1], O_RDONLY, 0);
    if (fd == -1)
    {
        perror("open");
        return open_err;
    }
    
    size = check_correct_format_matrix(fd);
    if (size == 0)
    {
        fprintf(stdout, "there is no elements\n");
        close(fd);
        return success_exit;
    }
    
    sum = summ_diag_matrix(fd, size);
    fprintf(stdout, "\n%lf\n", sum);
    
    close(fd);
    return success_exit;
}

