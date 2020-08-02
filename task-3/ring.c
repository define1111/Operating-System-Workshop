#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ring.h"

ring_t 
*init(char *str)
{
    ring_t *root = (ring_t*) malloc(sizeof(ring_t));
    if (root == NULL) return NULL;

    root->str = str;
    root->next = root;

    return root;
}

ring_t 
*add_item(ring_t *item, char *str)
{
    ring_t *temp, *next;

    temp = (ring_t*) malloc (sizeof(ring_t));
    if (item == NULL) return NULL;

    next = item->next;
    item->next = temp;
    temp->str = str;
    temp->next = next;

    return temp;    
}

void 
free_ring(ring_t *item)
{
    if (item)
    {
        free_ring(item->next);
        free(item->str);
        free(item);
    }
}

static ring_t *
prev(ring_t *item)
{
    ring_t *i;

    for (i = item->next; i->next != item; i = i->next)
        ;

    return i;
}

void 
cut_ring(ring_t *root)
{
    prev(root)->next = NULL;
}

void 
fprint_ring(FILE *f, ring_t *root)
{
    ring_t *next = root;

    do
    {
        fprintf(f, "%s\n", next->str);
        next = next->next;    
    } while (next != root);
}

ring_t *
find_lex_min(ring_t *root)
{
    ring_t *min = root, *next = root;
    
    do
    {
        if (strcmp(next->next->str, next->str) < 0) min = next->next;
        next = next->next;
    } while (next != root);

    return min;
}
