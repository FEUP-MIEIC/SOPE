/**
 * @file main_alt.c
 * @author Fábio Gaspar
 * @date 2018-02-28
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define S_BUFFER 256

int main(int argc, char** argv) {
    if(argc > 3) {
        printf("usage: %s source (destination)\n", argv[0]);
        exit(1);
    }

    int fd_src, fd_dst;

    // Open source file
    fd_src = open(argv[1], O_RDONLY);
    if(fd_src == -1) {
        perror(NULL);
        exit(2);
    }

    // Open the dest file if there's a third arg
    if(argc == 3) {
        fd_dst = open(argv[2], O_WRONLY | O_CREAT, 0555);
        
        if(fd_dst == -1) {
            perror(NULL);
            exit(3);
        }
        // Try to redirect STDOUT to dest file
        if(dup2(fd_dst, STDOUT_FILENO) == -1) {
            perror(NULL);
            exit(4);
        }
    }
    

    // Read from src and write to dst
    char buffer[S_BUFFER];
    int r_bytes;

    while((r_bytes = read(fd_src, buffer, S_BUFFER)) != 0) {
        // check for errors
        if(r_bytes == -1) {
            perror(NULL);
            exit(3);
        }

        // try to write to file
        if(write(STDOUT_FILENO, buffer, r_bytes) == -1) {
            perror(NULL);
            exit(4);
        }
    }

    // close files and restore STDOUT descriptor
    close(fd_src);
    if(argc == 3) close(fd_dst);

}