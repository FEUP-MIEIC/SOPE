/**
 * @file b.c
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

#define INVALID_ARGUMENTS -1
#define FAILED_IO -2

int main(int argc, char** argv) {
    if(argc != 3) {
        printf("usage: %s source destination\n", argv[0]);
        exit(INVALID_ARGUMENTS);
    }

    int fd_src, fd_dst;

    // Open source file
    fd_src = open(argv[1], O_RDONLY);
    if(fd_src == -1) {
        perror(NULL);
        exit(FAILED_IO);
    }

    // Open/Create dest file
    fd_dst = open(argv[2], O_WRONLY | O_CREAT, 0555);
    if(fd_dst == -1) {
        perror(NULL);
        exit(FAILED_IO);
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
        if(write(fd_dst, buffer, r_bytes) == -1) {
            perror(NULL);
            exit(4);
        }

        printf("%s\n", buffer);
    }

    // close files
    close(fd_src);
    close(fd_dst);
}