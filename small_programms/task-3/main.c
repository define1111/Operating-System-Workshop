#include <stdio.h>
#include <stdlib.h>
#include "ring.h"

enum { buffer_step = 16 };
enum { success_exit = 0, alloc_err };

char *read_str(FILE *f, size_t buffer_step)
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

char *check_read_str(FILE *f, size_t buffer_step)
{
    char *str = read_str(f, buffer_step);
    if (str == NULL)
    {
        perror("alloc");
        exit(alloc_err);
    }
    return str;
}

ring_t *check_init(char *str)
{
    ring_t *root = init(str);
    if (root == NULL)
    {
        perror("alloc");
        exit(alloc_err);
    }
    return root;
}

ring_t *check_add_item(ring_t *item, char *str)
{
    ring_t *temp = add_item(item, str);
    if (temp == NULL)
    {
        perror("alloc");
        exit(alloc_err);
    }
    return temp;
}

ring_t *make_ring()
{
    char  *str = check_read_str(stdin, buffer_step);
    ring_t *root = check_init(str);   
    ring_t *next = root;    

    while (*(str = check_read_str(stdin, buffer_step)))
        next = check_add_item(next, str);

    free(str);    
    return root;    
}

int main()
{
    ring_t *root = make_ring();
   
    root = find_lex_min(root);

    putc('\n', stdout); 
    fprint_ring(stdout, root);

    FREE_RING(root);
    
    return success_exit;
}


