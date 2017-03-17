// PROGRAMA p7.c
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int status;
	char prog[20];
	sprintf(prog,"%s.c",argv[1]);

	int pid=fork();
	if(pid>0){
		wait(&status);
		printf("Código de terminação: %i\n", WEXITSTATUS(status));
		exit(WEXITSTATUS(status));
	}else{
		execlp("gcc","gcc",prog,"-Wall","-o",argv[1],NULL);
	}
}
