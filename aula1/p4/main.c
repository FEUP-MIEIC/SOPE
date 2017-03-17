#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[], char* envp[]){
	if(argc < 2){
		printf("I must receive a name to greet!\n");
		exit(1);
	}

	int nTimes;

	if(argc == 3){
		nTimes=atoi(argv[2]);
	}else{
		nTimes=1;
	}

	if (nTimes<1){
		printf("I can't show a message less than 1 times!\n");
		exit(2);
	}

	int i;

	for(i=0; i < nTimes; i++){
		printf("Hello %s!\n", argv[1]);
	}

}
