#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

static const size_t max_stacksize = 32;

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

static void unexpected_end()
{
    fprintf(stderr, "unexpected end of input\n");
    exit(2);
}

int main(int argc, char** argv)
{
    long stack[max_stacksize];
    size_t stack_frame = 0;

    printf("> ");

    char input[1024];
    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        fprintf(stderr, "failed to read input\n");
        exit(2);
    }

    char* p = input;
    for (; *p != '\0'; p++)
    {
        skip_whitespaces(&p);

        if (isoperator(*p))
        {
            if (stack_frame < 2)
            {
                fprintf(stderr, "stack too small for operation\n");
                return 2;
            }

            char operator = *p;
            long a = stack[--stack_frame];
            long b = stack[--stack_frame];
            p++;

            if (operator == '+')
            {
                stack[stack_frame++] = a + b;
            }
            else if (operator == '-')
            {
                stack[stack_frame++] = a - b;
            }
            else if (operator == '*')
            {
                stack[stack_frame++] = a * b;
            }
            else if (operator == '/')
            {
                stack[stack_frame++] = a / b;
            }
        }
        else if (isdigit(*p))
        {
            if (stack_frame >= max_stacksize)
            {
                fprintf(stderr, "stack exceeded\n");
                exit(2);
            }

            // i'm not sure passing &p as endptr is portable *caugh*
            long v = strtol(p, &p, 0);
            stack[stack_frame++] = v;
        }
        else
        {
            unexpected_end();
        }
    }

    if (*p != '\0' || stack_frame != 1)
    {
        unexpected_end();
    }

    printf("= %li\n", stack[0]);

    return 0;
}
