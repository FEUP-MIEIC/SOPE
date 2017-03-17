#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


#define BUFFER_SIZE 10240

int min(int a, int b){
	if(a<b)
		return a;
	return b;
	
}

int main(int argc, char* argv[]){

	if(argc!=3){
		write(STDOUT_FILENO, "Utilização: ./a.out source dest\n", 34);
		return 1;
	}
	
	char buffer[BUFFER_SIZE];
	int src;
	int dst;
	int status, lSize;
	
	src=open(argv[1], O_RDONLY);
	//exit(1);
	if(src==-1){
		printf("There was an error opening the file %s for reading!\n", argv[1]);
		exit(1);
	}
	
	dst=open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0555);
	if(dst==-1){
		printf("There was an error opening the file %s for writing!\n", argv[2]);
		exit(1);
	}

	// obtain file size:
	lSize = lseek (src , 0, SEEK_END);
	lseek(src, 0, SEEK_SET);


	if(lSize>BUFFER_SIZE){
		printf("Source file is bigger than the available buffer! However, there are loops!\n");
	}
	int i=1;
	
	while((status=read(src, buffer, min(lSize, BUFFER_SIZE)))){
		//printf("Passagem %d: %d\n", i, status);
		write(dst, buffer, status);
		lSize-=status;
		i++;
		//sleep(1);
	}
	
	close(dst);
	close(src);
	return 0;
}
