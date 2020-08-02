#include <stdio.h>
#include <stdlib.h>
#include "ring.h"

enum { buffer_step = 16 };
enum { success_exit = 0, alloc_err };
  
char *
read_str()
{
    int ch = 0;
    char *str = NULL;
    size_t i = 0;

    while(1)
    {
        str = (char*) realloc(str, ++i * sizeof(char));
        if (str == NULL)
        {
            perror("realloc");
            exit(alloc_err);
        }

        ch = getchar();
        
        if (ch == '\n' || ch == EOF)
        {
            str[i - 1] = '\0';
            break;
        }
        
        str[i - 1] = (char) ch;
     }

     return str;
}

ring_t *
check_init(char *str)
{
    ring_t *root = init(str);
    if (root == NULL)
    {
        perror("alloc");
        exit(alloc_err);
    }
    return root;
}

ring_t *
check_add_item(ring_t *item, char *str)
{
    ring_t *temp = add_item(item, str);
    if (temp == NULL)
    {
        perror("alloc");
        exit(alloc_err);
    }
    return temp;
}

ring_t *
make_ring()
{
    char *str = read_str();
    ring_t *root = check_init(str);   
    ring_t *next = root;    

    while (*(str = read_str()))
        next = check_add_item(next, str);

    free(str);    
    return root;    
}

int 
main()
{
    ring_t *root = make_ring();
   
    root = find_lex_min(root);

    putc('\n', stdout);
    fprint_ring(stdout, root);

    FREE_RING(root);
    
    return success_exit;
}


