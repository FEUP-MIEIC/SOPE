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

    /*
    Upon successful completion fopen(), fdopen()  and  freopen()  return  a
       FILE pointer.  Otherwise, NULL is returned and errno is set to indicate
       the error.
    */

    // perror = "some error description by dev" + strerror(errno)
    if ((src = fopen("infile.txt", "r")) == NULL)
    {
        perror("Failed to open infile.txt");
        //printf("open infile.txt: %s\n", strerror(errno));
        exit(1);
    }
    if ((dst = fopen("outfile.txt", "w")) == NULL) // fopen on write only mode doesn't return an error if the file is missing. It creates the file
    {
        perror("Failed to open outfile.txt");
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