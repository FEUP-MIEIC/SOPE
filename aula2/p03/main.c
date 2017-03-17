#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>

char* intToStr(char* str, int x){
	int y, i=0;
	while(x>0){
		printf("%d\n", x);
		y=x%10;
		x=x/10;
		str[i]=y+48;
		i++;
	}
	str[i]='\0';
}

int main(int argc, char** argv){
	if(argc<2){
		write(STDOUT_FILENO, "A file must be passed!\nusage: show <file>\n", 42);
		exit(1);
	}

	int r = open(argv[1], O_RDONLY);
	if(r==-1){
		write(STDOUT_FILENO, "The specified file could not be opened for reading!\n", 52);
		char error[6];
		intToStr(error, 4325);
		write(STDOUT_FILENO, error, 4);
	}
	return 0;
}
