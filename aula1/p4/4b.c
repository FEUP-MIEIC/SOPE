#include <stdio.h>
#include <stdlib.h>
int main(int argc, char** argv)
{
    if(argc < 3) {
        printf("Missing arguments!\n");
        exit(-1);
    }

    // atoi returns 0 if there's no valid conversion
    for(int i = 0; i < atoi(argv[argc-1]); i++) {
        printf("Hello ");
        for(int j = 1; j < argc-1; j++) {
            printf("%s ", argv[j]);
        }
        printf("!\n");
        
    }
    
}