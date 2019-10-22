#ifndef READ_STR_SENTRY
#define READ_STR_SENTRY

#define EOF (-1)
#define BUFFER_SIZE 16

extern int is_EOF;

char *fd_read_str(int fd);
int fd_put_string(int fd, const char *str);
int fd_put_char(int fd, char ch);
int put_string(const char *str);
int put_char(char ch);

int string_length(const char *str);

#endif
