#include <stdio.h>

int main (int argc, char * argv[]){
	
	if (argc !=  3) {
		perror("Error: 2 arguments needed");
	}
	
	//char* hostString = argv[1];
	//char* filePath = argv[2];	
	
   printf("Hello %s %s %s", argv[0], argv[1], argv[2]);
   return 0;
}
