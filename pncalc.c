#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

static void unexpected_end()
{
    fprintf(stderr, "unexpected end of input\n");
    exit(2);
}

static int isoperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

static void skip_whitespaces(char** p)
{
    while (isspace(**p))
    {
        *p += 1;
    }
}

static long get_next(char** p)
{
    skip_whitespaces(p);

    if (isoperator(**p))
    {
        char operator = **p;
        *p += 1;
        int a = get_next(p);
        int b = get_next(p);

        if (operator == '+')
        {
            return a + b;
        }
        else if (operator == '-')
        {
            return a - b;
        }
        else if (operator == '*')
        {
            return a * b;
        }
        else if (operator == '/')
        {
            return a / b;
        }
    }
    else if (isdigit(**p))
    {
        // i'm not sure passing &p as endptr is portable *caugh*
        return strtol(*p, p, 0);
    }

    unexpected_end();
    return 0; // never reached
}

int main(int argc, char** argv)
{
    printf("> ");

    char input[1024];
    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        fprintf(stderr, "failed to read input\n");
        exit(2);
    }

    char* p = input;
    long r = get_next(&p);

    if (*p != '\n')
    {
        unexpected_end();
    }

    printf("= %li\n", r);

    return 0;
}
