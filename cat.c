#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_STDIN_SIZE 1000   //you can change max size of stdin

int main(int argc,char **argv){
	
	int line_counter=0;
	if(argc>1){
		int fd;
		int bytes_read=0;
		char buf[1];

		fd=open(argv[1],O_RDONLY);

		 while((bytes_read=read(fd,buf,1))!=0 && bytes_read!=-1){ 
 				fprintf(stdout, "%c",buf[0]);
		 }

	}
	else{
		
		char buf;
		while(scanf("%c",&buf) && !feof(stdin)){
			fprintf(stdout, "%c",buf);
		}

	}

	return 1;

}