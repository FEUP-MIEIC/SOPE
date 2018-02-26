// PROGRAMA p6a.c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


#define BUF_LENGTH 256

void showUsage(char *exe) {
    printf("Usage: %s file1 file2\n", exe);
}

int main(int argc, char **argv)
{
    if(argc != 3) {
        showUsage(*argv);
        exit(3);
    }

    FILE *src, *dst;
    char buf[BUF_LENGTH];

    if ((src = fopen(*(argv+1), "r")) == NULL)
    {
        sprintf(buf, "Failed to open %s", *(argv+1)); // re-using buffer to build error descriptions
        perror(buf);
        exit(1);
    }
    if ((dst = fopen(*(argv+2), "w")) == NULL)
    {
        sprintf(buf, "Failed to open %s", *(argv+2)); // re-using buffer to build error descriptions
        perror(buf);
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