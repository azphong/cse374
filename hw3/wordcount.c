#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	if(argc < 2){
		fprintf(stderr, "Usage: %s requires an input file.\n", argv[0]);
		return 1;
	}
	if(strcmp(argv[1], "-l")==0){
		lc = true;
	}
	if(strcmp(argv[1], "-w")==0){
		wc = true;
	}
	return 0;
}
