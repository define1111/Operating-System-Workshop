#include <stdio.h>
#include <stdlib.h>

enum { byte_size = 8 };

__int8_t check_bit(__int32_t value, size_t position)
{
    const static __int32_t one_32bit = 1;
    return !!(value & (one_32bit << position));
}

void println_bits(__int32_t value)
{
    size_t i = byte_size * sizeof(__int32_t) - 1;

    while (i --> 0)
    {
        printf("%hd", check_bit(value, i));
    }

    putc('\n', stdout);
}

void loop()
{
    __int32_t num = 0;
    __int32_t scanf_return = 0;

    for(;;)
    {
        printf(">>> ");
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

int main()
{
    loop();

    return 0;
}
