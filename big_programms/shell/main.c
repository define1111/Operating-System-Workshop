#include <stdlib.h>
#include <stdio.h>
#include "inc/main.h"

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
    promt();  
    putc('\n', stdout);
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
    printf("%s:%s$ ", user, pwd);
}

