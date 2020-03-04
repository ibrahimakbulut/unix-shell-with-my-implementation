#include <unistd.h>
#include <stdio.h>
#include <limits.h>

#define MAX_SIZE_OF_PATH 250

void printCurrentDirectory();

int main(){

	printCurrentDirectory();

	return 0;
}

void printCurrentDirectory(){

   char current_directory[MAX_SIZE_OF_PATH];
   if (getcwd(current_directory, sizeof(current_directory)) != NULL) {
   	fprintf( stdout, "%s\n",current_directory );
       //printf("%s\n", current_directory);
   } else {
       perror("ERROR WİTH PWD");
   }
   return;

}
	
