#include <stdio.h>
#include <string.h>

int main(int argc, char **argv, char **envp) {
    for(; *envp != NULL && strncmp("USER", *envp, 4); envp++) {};
    
    if(*envp != NULL) {
        printf("Hello %s!\n", *(envp));
    }
}