#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>


#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_COMMANDLINE_SIZE 1000
#define MAX_COMMAND 1000


void redirection(char *commands,char* root_path);

void redirection2(char *commands,char* root_path);
static void SignalHandler(int SignalNo);

int main (int argc,char **argv){

	struct sigaction sa;

	memset(&sa,0,sizeof(sa));

	sa.sa_handler=&SignalHandler;

	sigaction(SIGTERM,&sa,NULL);

	char commands[MAX_COMMANDLINE_SIZE];

	char all_commands[MAX_COMMAND][MAX_COMMANDLINE_SIZE];
	int command_counter=0;
	int i=0;
	int j=0;

	printf("%d\n",(int)getpid());


	for(i=0;i<MAX_COMMAND;++i){
		memset(all_commands[i],'\0',MAX_COMMANDLINE_SIZE*sizeof(char));
	}
	i=0;

		char root_path[255];
		memset(root_path,'\0',255);
		getcwd(root_path,sizeof(root_path));
		strcat(root_path,"/");



	while(1){

		memset(commands,'\0',MAX_COMMANDLINE_SIZE*sizeof(char));
		read(STDIN_FILENO,commands,MAX_COMMANDLINE_SIZE);

		int a=strlen(commands)-1;

		commands[a]='\0';


		i++;


		int n_command=0;
		if(commands[strlen(commands)-1]=='!'){

			n_command=1;

			commands[strlen(commands)-1]=='\0';
			int a=atoi(commands);

			memset(commands,'\0',MAX_COMMANDLINE_SIZE*sizeof(char));
			strcpy(commands,all_commands[command_counter-a]);
		}
		if(commands[0]=='c' && commands[1]=='d'){
			chdir(&commands[3]);

			if(n_command==0){
			strcpy(all_commands[command_counter],commands);
			command_counter+=1;
			}
			continue;
		}
		if(commands[0]=='h' && commands[1]=='e' && commands[2]=='l' && commands[3]=='p'){
			printf("lsf\n");
			printf("pwd\n");
			printf("cat\n");
			printf("help\n");
			printf("cd\n");
			printf("wc\n");
			printf("bunedu\n");
			printf("exit\n");
			if(n_command==0){
			strcpy(all_commands[command_counter],commands);
			command_counter+=1;
			}
			continue;

		}


		if(strcmp(commands,"exit")==0){
			if(n_command==0){
			strcpy(all_commands[command_counter],commands);
			command_counter+=1;
			}
			return 0;;
		}

		int flag=0;
		char operator;

		for(i=0;i<strlen(commands);++i){
			
			if(commands[i]=='|'){
				flag=1;
				operator=commands[i];
				
			}
			else if(commands[i]=='>'){
				flag=2;
				operator=commands[i];
				
			}
			else if(commands[i]=='<'){
				flag=3;
				operator=commands[i];
			}
		}

		if(flag==0){
			if(n_command==0){
			strcpy(all_commands[command_counter],commands);
			command_counter+=1;
			}

		char **argvs=(char **)malloc(sizeof(char *)*100);

		for(i=0;i<100;i++){
			argvs[i]=(char *)malloc(sizeof(char)*100);
		}
		for(i=0;i<100;++i){
			memset(argvs[i],'\0',100*sizeof(char));
		}

		int space_counter=0;

		for(i=0;i<strlen(commands);++i){
			if(i==0){
				strcat(argvs[0],root_path);
			}
			char buf[2];
			buf[0]=commands[i];
			buf[1]='\0';
			if(buf[0]!=' ')

				strcat(argvs[space_counter],buf);
			else if(buf[0]==' ')
				space_counter+=1;
			
		}
		free(argvs[space_counter+1]);
		argvs[space_counter+1]=NULL;

			int new_fork=fork();

			if(new_fork==0){

				
				execv(argvs[0],argvs);
			}
			else{
				wait(NULL);


			}
		for(i=0;i<100;i++){
			free(argvs[i]);
		}
		free(argvs);


		}
		else if(flag==1){
			if(n_command==0){
			strcpy(all_commands[command_counter],commands);
			command_counter+=1;
			}
			redirection(commands,root_path);

		}
		else if(flag==2 || flag==3){
			if(n_command==0){
			strcpy(all_commands[command_counter],commands);
			command_counter+=1;
			}
			redirection2(commands,root_path);
		}

	}

	return 0;

}

static void SignalHandler(int SignalNo){

	printf("exiting from shell!\n");

	exit(0);

}

void redirection2(char *commands,char *root_path){

	int i=0;
	char redirection;
	int space_counter=0;
	int first_command_counter=0;
	int flag=0;

	char file[255];

	char **first_command=(char **)malloc(sizeof(char*)*255);
	for(;i<255;++i){
		first_command[i]=(char*)malloc(sizeof(char)*255);
	}
	for(i=0;i<255;++i){
	memset(first_command[i],'\0',255*sizeof(char));
	}
	memset(file,'\0',255*sizeof(char));

		for(i=0;i<strlen(commands);++i){
			if(i==0){
				strcat(first_command[0],root_path);
			}
				

			char buf[2];
			buf[0]=commands[i];
			buf[1]='\0';
			if(buf[0]=='>' || buf[0]=='<'){
				flag=1;
				if(buf[0]=='>')
					redirection='>';
				else{
					redirection='<';
				}
				space_counter=0;
			}
			else if(buf[0]!=' ' && flag==0){
				strcat(first_command[first_command_counter],buf);
				space_counter=0;
			}
			else if(buf[0]!=' ' && flag==1){
				strcat(file,buf);
			}
			else if(buf[0]==' ' && flag==0 && space_counter==0){
				first_command_counter+=1;
				space_counter+=1;
			}
			else
				space_counter+=1;

		}
		free(first_command[first_command_counter]);           
		first_command[first_command_counter]=NULL;

		if(redirection=='>'){

			int new_fork=fork();
			if(new_fork==0){
	
			
			//printf("%s\n",first_command[first_command_counter]);
			int fd = open(file, O_WRONLY | O_CREAT | O_TRUNC,0644);
			dup2(fd,STDOUT_FILENO);
			

			execv(first_command[0],first_command);
			close(fd);
			}
			else
				wait(NULL);
			
		}
		else{

			int new_fork=fork();
			if(new_fork==0){
			int fd=open(file, O_RDONLY,0644);
			dup2(fd,STDIN_FILENO);
			

		
			printf("%s\n",file);
			execv(first_command[0],first_command);
			close(fd);
			}
			else
				wait(NULL);

		}

		for(i=0;i<255;++i){
			free(first_command[i]);
		}
		free(first_command);
}

void redirection(char *commands,char *root_path){

	int i=0;
	char **first_command=(char **)malloc(sizeof(char*)*255);
	char **second_command=(char **)malloc(sizeof(char*)*255);

	for(;i<255;++i){
		first_command[i]=(char*)malloc(sizeof(char)*255);
		second_command[i]=(char*)malloc(sizeof(char)*255);
	}
	for(i=0;i<255;++i){
	memset(first_command[i],'\0',255*sizeof(char));
	memset(second_command[i],'\0',255*sizeof(char));
	}

	int flag=0;
	int j=-1;

	int first_command_counter=0;
	int second_command_counter=0;
	int space_counter=0;

		for(i=0;i<strlen(commands);++i){
			if(i==0){
				strcat(first_command[0],root_path);
			}
				
			char buf[2];
			buf[0]=commands[i];
			buf[1]='\0';
			if(buf[0]=='|'){
				flag=1;
				strcat(second_command[0],root_path);
				j=1;
				space_counter=0;
				second_command_counter=-1;
			}
			else if(buf[0]!=' ' && flag==0){
				strcat(first_command[first_command_counter],buf);
				space_counter=0;
			}
			else if(buf[0]!=' ' && flag==1){
				strcat(second_command[second_command_counter],buf);
				space_counter=0;
				j++;
			}
			else if(buf[0]==' ' && flag==0 && space_counter==0){
				first_command_counter+=1;
				space_counter+=1;
			}
			else if(buf[0]==' ' && flag==1 && space_counter==0){
				second_command_counter+=1;
				space_counter+=1;
				j++;
			}
			else
				space_counter+=1;

			
		}
		free(first_command[first_command_counter+1]);
		free(second_command[second_command_counter+1]);

		first_command[first_command_counter+1]=NULL;
		second_command[second_command_counter+1]=NULL;


		int fd[2];

		pipe(fd);
		int new_fork=fork();


		if(new_fork==0){

			close(fd[0]);
			dup2(fd[1],STDOUT_FILENO);
			close(fd[1]);
			

			execv(first_command[0],first_command);


		}
		else{
			;
		}

		new_fork=fork();


		if(new_fork==0){

			close(fd[1]);
			dup2(fd[0],STDIN_FILENO);
			
			close(fd[0]);

			execv(second_command[0],second_command);
		}
		else{
			;
		}

		close(fd[0]);
		close(fd[1]);

				wait(NULL);
				wait(NULL);


		for(i=0;i<255;++i){
			free(first_command[i]);
			free(second_command[i]);
		}
		free(first_command);
		free(second_command);

}
