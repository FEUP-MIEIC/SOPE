// PROGRAM p06.c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <wait.h>

void myHandler(int signo){
    int status;
    pid_t pid = wait(&status); 
    printf("Child %d terminated.\n", pid); 
    exit(0);    
}

int main(int argc, char** argv) 
{ 
	pid_t pid; 
	int status; 
	
    pid=fork(); 

    if (pid == 0){ 
        printf("A executar %s\n", argv[2]);
        execv(argv[2], &argv[2]);
        printf("O programa pedido não foi encontrado!\n");
        exit(0); 
    } 

    signal(SIGCHLD, myHandler);
    sleep(atoi(argv[1]));
    kill(pid, SIGKILL);
    printf("Program killed.\n");
    

	 
} 