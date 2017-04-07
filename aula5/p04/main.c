#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv){
	if(argc<3){ /******		Error checking 		*****/
		printf("Error! I must get two arguments!\n");
		exit(-1);
	}

	int pfd1[2], pfd2[2], pfd3[2];

	if(pipe(pfd1)==-1){ /******		Error checking 		*****/
		printf("Error! Could not open pipe!\n");
		exit(-3);
	};

	if(fork()==0){ // child
		close(pfd1[0]); // close read pipe;
		dup2(pfd1[1], STDOUT_FILENO);
		execlp("ls", "ls", argv[1], NULL);
		printf("Error calling ls!\n");
		exit(-10);
	}
	close(pfd1[1]); // close write pipe;

	if(pipe(pfd2)==-1){ /******		Error checking 		*****/
		printf("Error! Could not open pipe!\n");
		exit(-3);
	};

	close(pfd2[1]); // close write pipe;
	if(fork()==0){ // child
		close(pfd2[0]); // close read pipe;
		dup2(pfd1[0], STDIN_FILENO);
		dup2(pfd2[1], STDOUT_FILENO);
		execlp("grep", "grep", argv[2], NULL);
		printf("Error calling grep!\n");
		exit(-10);
	}

	if(pipe(pfd3)==-1){ /******		Error checking 		*****/
		printf("Error! Could not open pipe!\n");
		exit(-3);
	};

	if(fork()==0){ // child
		close(pfd2[1]); // close write pipe;
		close(pfd1[0]); // close read pipe;
		dup2(pfd2[0], STDIN_FILENO);
		dup2(pfd3[1], STDOUT_FILENO);
		execlp("sort", "sort", NULL);
		printf("Error calling sort!\n");
		exit(-10);
	}

	// Parent

	close(pfd3[1]); // close write pipe

	char* buf=malloc(100);
	int rr;
	while((rr=read(pfd3[0], buf, 100))>0){
		write(STDOUT_FILENO, buf, rr);
	}

	free(buf);

	return 0;
}
