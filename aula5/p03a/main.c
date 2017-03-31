#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv){
	if(argc!=2){ /******		Error checking 		*****/
		printf("Error! I must get one argument!\n");
		exit(-1);
	}

	FILE* f;
	f=fopen(argv[1], "r");

	if(f==NULL){ /******		Error checking 		*****/
		printf("Error! Could not open file!\n");
		exit(-2);
	}
	int pfd[2], pfd2[2];
	if(pipe(pfd)==-1){ /******		Error checking 		*****/
		printf("Error! Could not open pipe!\n");
		exit(-3);
	};
	if(pipe(pfd2)==-1){ /******		Error checking 		*****/
		printf("Error! Could not open pipe!\n");
		exit(-3);
	};

	if(fork()==0){ // child
		close(pfd[1]); // close write pipe;
		close(pfd2[0]); // close read pipe;
		//close(STDIN_FILENO);
		dup2(pfd[0], STDIN_FILENO);
		dup2(pfd2[1], STDOUT_FILENO);
		execlp("sort", "sort", NULL);
		printf("Error calling exec!\n");
		exit(-10);
	}

	// Parent

	close(pfd[0]); // close read pipe
	close(pfd2[1]); // close write pipe

	fseek(f, 0, SEEK_END);
	long fsize=ftell(f);
	//printf("Read %li bytes.\n", fsize);

	char* buf=calloc(fsize+1, 1);
	fseek(f, 0, SEEK_SET);

	char c;
	int i=0;
	while((c=getc(f))!=EOF){
		buf[i++]=c;
	}

	write(pfd[1], buf, fsize);
	close(pfd[1]);
	fclose(f);

	read(pfd2[0], buf, fsize+1);

	printf("%s", buf);

	free(buf);
}
