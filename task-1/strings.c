#include <stdio.h>
#include <stdlib.h>

char *
read_str()
{
    int ch = 0;
    char *str = NULL;
    size_t i = 0;

    while (1)
    {
        str = (char*) realloc(str, ++i * sizeof(char));
        if (str == NULL)
        {
            perror("realloc");
            exit(1);
        }

        ch = getchar();

        if (ch == EOF || ch == '\n')
        {
            str[i - 1] = '\0';
            break;
        }

        str[i - 1] = (char) ch;
    }

    return str;
}

int 
main()
{
    char *str = read_str();

    if (!*str)
    {
        free(str);
        return 0;
    }

    main();

    puts(str);
    free(str);
}
