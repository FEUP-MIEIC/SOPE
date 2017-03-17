// PROGRAM p07.c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <wait.h>


int main(int argc, char** argv) 
{ 

	int it=1;

	while(argv[it]!=NULL){
		if(fork()==0){
			execlp(argv[it], argv[it], NULL);
			printf("Failed to run %s.\n", argv[it]);
			exit(-1);
		}
		it++;
	}
	int status;
	while(1){
		int ret = waitpid(-1, &status, WNOHANG);
		if(ret==-1){ // No children remaining
			printf("All children ran successfully.\n");
			break;
		}else if(ret==0){ // There are still children running
			usleep(100);
		}else{ // We got someone
			printf("Child %d existed with code %d.\n", ret, WEXITSTATUS(status));
		}
	}
} 