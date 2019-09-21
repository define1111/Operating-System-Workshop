#include <stdlib.h>
#include <stdio.h>

#include "inc/main.h"
#include "inc/read_str.h"

enum { buffer_size = 16 };

static void init(void);
static void loop(void);
static void promt(void);

int
main(int argc, char **argv)
{
    init();
    
    loop();

    goodbye();
}

void
init()
{
    
}

void 
loop()
{
    char *input_str = NULL;
    
    for (;;)
    {
        promt();
        input_str = read_str(stdin, buffer_size); 
        puts(input_str);
        free(input_str);
        input_str = NULL;
    }
}

void 
goodbye()
{
   exit(0); 
}

void 
promt()
{
    char *user = getenv("USER");
    char *pwd = getenv("PWD");
    printf(MAGNETA "[toy_shell]" GREEN "%s" WHITE ":" BLUE "%s" WHITE "$ ", user, pwd);
}
