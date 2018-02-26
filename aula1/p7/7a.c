#include <stdio.h>
#include <stdlib.h>

void bye(void)
{
    printf("1-- prepping\n");
    //exit(-9);
    printf("1-- That was all, folks\n");
}

void bye2(void)
{
    printf("2-- prepping\n");
    //exit(-9);
    printf("2-- That was all, folks\n");
}

int main(void)
{

    printf("Setting exit handler 1.\n");
    if (atexit(bye))
    {
        fprintf(stderr, "cannot set exit function\n");
        exit(EXIT_FAILURE);
    }

    printf("Setting exit handler 1 again.\n");
    if (atexit(bye))
    {
        fprintf(stderr, "cannot set exit function\n");
        exit(EXIT_FAILURE);
    }

    printf("Setting exit handler 2.\n");
    if (atexit(bye2))
    {
        fprintf(stderr, "cannot set exit function\n");
        exit(EXIT_FAILURE);
    }

    //abort();
    printf("Main done!\n");
    //exit(EXIT_FAILURE);

    //exit(EXIT_SUCCESS);

    return 0;
}
