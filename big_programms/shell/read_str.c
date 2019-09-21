#include <stdio.h>
#include <stdlib.h>
#include "inc/read_str.h"

char *
read_str(FILE *f, size_t buffer_step)
{
    __int32_t ch = 0;
    char *str = NULL;
    size_t i = 0;

    str = (char*) malloc(buffer_step * sizeof(char));
    if (str == NULL) return NULL;
    
    for(;;i++)
    {
        ch = fgetc(f);
        
        if (ch == '\n' || ch == EOF)
        {
            if (i % buffer_step == 0)
            {
                str = (char*) realloc(str, (i + 1) * sizeof(char));
                if (str == NULL) return NULL;
            }

            str[i] = '\0';
            return str;
        }

        if (i % buffer_step == 0)
        {
            str = (char*) realloc(str, (i + buffer_step) * sizeof(char));
            if (str == NULL) return NULL;
        }
        
        str[i] = (char) ch;
    }
}
