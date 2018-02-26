// PROGRAMA p6a.c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


#define BUF_LENGTH 256

int main(void)
{
    FILE *src, *dst;
    char buf[BUF_LENGTH];

    if ((src = fopen("infile.txt", "r")) == NULL)
    {
        printf("error code: %d\n", errno);
        exit(1);
    }
    if ((dst = fopen("outfile.txt", "w")) == NULL) // fopen on write only mode doesn't return an error if the file is missing. It creates the file
    {
        printf("error code: %d\n", errno);
        exit(2);
    }
    while ((fgets(buf, BUF_LENGTH-1, src)) != NULL)
    {
        fputs(buf, dst);
    }
    
    fclose(src);
    fclose(dst);
    exit(0); // zero é geralmente indicativo de "sucesso"
}