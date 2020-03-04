#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include "bunedu.h"

int program_mode=0;

int main(int argc,char **argv)
{
	if(argc==2 && (strcmp(argv[1],"-z")==0)){
		char path[255];
		memset(path,'\0',255);
		scanf("%s",path);
		program_mode=2;
		deptFirstApply(path,sizepathfun);
		return 0;

	}
	else if(argc==1){
		char path[255];
		memset(path,'\0',255);
		scanf("%s",path);
		program_mode=1;
		deptFirstApply(path,sizepathfun);
		return 0;

	}
	else if(argc!=2 && argc!=3){
	printf("Program must be called -- %s buNeDu [-z] rootpath-- or  -- %s buNeDu rootpath -- \n",argv[0],argv[0]);
	return 1;
	}
	else if(argc==2 && (strcmp(argv[1],"-z")==0)){
	printf("Program must be called -- %s buNeDu [-z] rootpath-- or  -- %s buNeDu rootpath -- \n",argv[0],argv[0]);
	return 1;
	}
	else if(argc==2 && (argv[1][0]!='/')){
	printf("Pathname must be start with \"/\" \n");
	return 1;
	}
	else if(argc==2){
	program_mode=1;
	deptFirstApply(argv[1],sizepathfun);
	return 0;
	}
	else if(argc==3 && (strcmp(argv[1],"-z")!=0)){
	printf("Program must be called -- %s buNeDu [-z] rootpath-- or  -- %s buNeDu rootpath -- \n",argv[0],argv[0]);
	return 1;
	}
	else if(argc==3 && (argv[2][0]!='/') ){
	printf("Pathname must be start with \"/\" \n");
	return 1;
	}
	else{
	program_mode=2;
	deptFirstApply(argv[2],sizepathfun);
	return 0;
	}
	
}

int deptFirstApply (char *basePath,int pathfun (char *path1))
{
    char *path;
    struct stat stat_buffer;
    struct dirent *dp;
    DIR *dir = opendir(basePath);
    int total=0;
    int total_total=0;
 

    // Unable to open directory stream
    if (dir==NULL) {
        return -1;
	}
		
    while ((dp = readdir(dir)) != NULL)
    {
	total=0;
	

	        path=(char *)malloc(strlen(basePath)+strlen(dp->d_name)+2);
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0){
            


	 	
	    //lstat(path,&stat_buffer);
	    if (lstat(path, &stat_buffer) ==0){
	    if(S_ISDIR(stat_buffer.st_mode)){

			total=deptFirstApply(path,sizepathfun);
			if(total==-1){

					printf("Cannot read folder %s\n",path);
					total=0;
   				}

			if(program_mode==2)
				total_total+=total;
		}

	    else if(sizepathfun(path)==-1){
			printf("special file %s \n",dp->d_name);
			total_total+=total;
		}
	   
        else if(sizepathfun(path)>0){
			total+=sizepathfun(path);
			//printf("%d  \n",total/1024,path);
			total_total+=total;
	    }
	   }
		}
		 free(path);
    }

	printf("%d %s\n",total_total,basePath);
	

		
 	closedir(dir);
	return total_total;


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












