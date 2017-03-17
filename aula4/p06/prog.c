#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    int i=0;
    while(i<3){
        printf("%s\n", argv[1]);
        i++;
        sleep(4);
    }
}