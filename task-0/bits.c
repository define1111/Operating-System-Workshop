#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

enum { byte_size = 8 };
const int32_t one_32bit = 1;

int 
check_bit(int32_t value, size_t position)
{
    return !!(value & (one_32bit << position));
}

void 
println_bits(int32_t value)
{
    size_t i = byte_size * sizeof(int32_t);

    while (i --> 0)
    {
        printf("%hd", check_bit(value, i));
    }

    putc('\n', stdout);
}

void 
loop()
{
    int32_t num = 0;
    int32_t scanf_return = 0;

    while (1)
    {
        fputs(">>> ", stdout);
        scanf_return = scanf("%d", &num);
        
        switch (scanf_return)    
        {
            case 0:
                scanf("%*[^\n]");
                break;
            case EOF:
                putc('\n', stdout);
                return;
            default:
                println_bits(num);
        }    
    }
}

int 
main()
{
    loop();

    return 0;
}
