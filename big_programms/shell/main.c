#include <stdlib.h>

#include "inc/main.h"
#include "inc/io.h"

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
        input_str = fd_read_str(0); 
        put_string(input_str);
        put_char('\n');
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
   // printf(YELLOW "[toy_shell]" GREEN "%s" WHITE ":" BLUE "%s" WHITE "$ ", user, pwd);
    fd_put_string(1, YELLOW "[toy_shell]" GREEN);
    fd_put_string(1, user);
    fd_put_string(1, WHITE ":" BLUE);
    fd_put_string(1, pwd);
    fd_put_string(1, WHITE "$ ");
}
