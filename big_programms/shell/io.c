#include <stdlib.h>
#include <unistd.h>

#include "inc/io.h"


int is_EOF = 0;

static int 
fd_get_char(int fd)
{
    static char buf[BUFFER_SIZE];
    static char *bufp = buf;
    static int n = 0;

    if (n == 0) /* buffer is empty */
    {
        n = read(0, buf, BUFFER_SIZE * sizeof(char));
        bufp = buf;
    }

    return (--n >= 0) ? (unsigned char) *bufp++ : EOF;
}

char *
fd_read_str(int fd)
{
    int ch = 0;
    char *str = NULL;
    size_t i;
    
    is_EOF = 0;
    
    for(i = 0; ; ++i)
    {
        ch = fd_get_char(fd);
        
        if (ch == '\n' || ch == EOF)
        {
            if (i % BUFFER_SIZE == 0)
            {
                str = realloc(str, (i + 1) * sizeof(char)); 
                if (str == NULL) return NULL;
            }
            
            str[i] = '\0';            
            if (ch == EOF) is_EOF = 1;
    
            return str;
        }
        
        if (i % BUFFER_SIZE == 0)
        {    
            str = realloc(str, (i + BUFFER_SIZE) * sizeof(char));
            if (str == NULL) return NULL;
        }
        
        str[i] = (char) ch;
    }
}

int
string_length(const char *str)
{
    const char *p;
    
    for (p = str; *p; ++p)
        ;
    
    return p - str;
}

int
fd_put_string(int fd, const char *str)
{
    return write(fd, str, string_length(str));
}

int
fd_put_char(int fd, char ch)
{
    return write(fd, &ch, sizeof(char));
}

int
put_string(const char *str)
{
    return write(1, str, string_length(str));
}

int
put_char(char ch)
{
    return write(1, &ch, sizeof(char));
}
