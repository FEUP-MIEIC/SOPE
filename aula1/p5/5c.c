#include <stdio.h>
#include <stdlib.h>

int main() {
    char * str = getenv("USER");
    if(str != NULL) printf("Hello %s!\n", str);
}