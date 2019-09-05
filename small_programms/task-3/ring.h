#ifndef RING_H_SENTRY
#define RING_H_SENTRY

struct ring
{
    char *str;
    struct ring *next;
};

typedef struct ring ring_t;

ring_t *init(char *str);
ring_t *add_item(ring_t *item, char *str);
void free_ring(ring_t *item);
void cut_ring(ring_t *root);
void fprint_ring(FILE *f, ring_t *root);
ring_t *find_lex_min(ring_t *root);

#define FREE_RING(item) \
cut_ring(item); \
free_ring(item); \


#endif
