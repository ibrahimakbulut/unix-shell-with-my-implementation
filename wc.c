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

		 while((bytes_read=read(fd,buf,1))!=0 && bytes_read!=-1 && buf[0]!='\0'){

		 	if(buf[0]=='\n')
		 		line_counter+=1;
		 }

		 fprintf(stdout, "%d\n",line_counter);

		 return line_counter;

	}
	else{
		char buf;
		while(scanf("%c",&buf) && !feof(stdin)){
			if(buf=='\n')
				line_counter+=1;
		}

		fprintf(stdout,"%d\n",(line_counter));
		return (line_counter);

	}

}