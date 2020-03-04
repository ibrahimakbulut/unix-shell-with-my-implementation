
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX_SIZE_OF_PATH 250






int sizepathfun (char *path);

void working_directory_files_information(){

 char current_directory[MAX_SIZE_OF_PATH];
 char *path;

 struct stat stat_buffer;
 struct dirent *dp;
 getcwd(current_directory, sizeof(current_directory));
 DIR *dir = opendir(current_directory);


    while ((dp = readdir(dir)) != NULL)
    {

    		path=(char *)malloc(strlen(current_directory)+strlen(dp->d_name)+2);
            strcpy(path, current_directory);
            strcat(path, "/");
            strcat(path, dp->d_name);

           	if (lstat(path, &stat_buffer) ==0){
	    		if(!(S_ISDIR(stat_buffer.st_mode))){
	    			if(sizepathfun(path)==-1){
	    				printf("S ");
	    			}
	    			else
	    				printf("R ");
	    			if(stat_buffer.st_mode & S_IRUSR)
	    				printf("r");
	    			else
	    				printf("-");
	    			if(stat_buffer.st_mode & S_IWUSR)
	    				printf("w");
	    			else
	    				printf("-");
	    			if(stat_buffer.st_mode & S_IXUSR)
	    				printf("x");
	    			else
	    				printf("-");
	    			if(stat_buffer.st_mode & S_IRGRP)
	    				printf("r");
	    			else
	    				printf("-");
	    			if(stat_buffer.st_mode & S_IWGRP)
	    				printf("w");
	    			else
	    				printf("-");
	    			if(stat_buffer.st_mode & S_IXGRP)
	    				printf("x");
	    			else
	    				printf("-");
	    			if(stat_buffer.st_mode & S_IROTH)
	    				printf("r");
	    			else
	    				printf("-");
	    			if(stat_buffer.st_mode & S_IWOTH)
	    				printf("w");
	    			else
	    				printf("-");
	    			if(stat_buffer.st_mode & S_IXOTH)
	    				printf("x");
	    			else
	    				printf("-");

	    			printf(" ");
	    			printf("%d ",(int)stat_buffer.st_size);
	    			printf("%s\n",dp->d_name);

	    		}
	    	}
	    	free(path);
}
closedir(dir);
}
int main(){
	working_directory_files_information();
	return 0;
}


int sizepathfun (char *path){

struct stat statbuf;

if (lstat(path, &statbuf) !=0)
return -2;
else if(!(S_ISREG(statbuf.st_mode)) && !(S_ISDIR(statbuf.st_mode)) ){ // if special file
return -1;
}

else return ((int)statbuf.st_size);
}