#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	char opt[];
	int start;
	if(argc < 2){
		fprintf(stderr, "Usage: %s requires an input file.\n", argv[0]);
		return 1;
	}
	if(argv[1] == "-l" || argv[1] == "-w" || argv[1] == "-c"){
		opt = argv[1];
		start = 2;
	} else {
		opt = ' ';
		start = 1;
	}
	for(int i = start; i < argc; i++){
		FILE* fp = fopen(argv[i], "r");
		process_file(fp, opt);
	}
	return 0;
}

void process_file(FILE* fp, char opt[]){
	int l, w, c;
	char ch;
	l = 0;
	w = 0;
	c = 0;
	if(fp != NULL){
		while ((ch = getc(fp)) != EOF){
			if(ch == '\n'){
				l++;	
			}
			if(ch == ' ' || ch == '\n'){
				w++;
			}
			if(ch != ' ' && ch != '\n'){
				c++;
			}
		}
		switch(opt){
			case "-l":	
		}
	} else {
		printf("%s will not open. Skipping.\n", argv[i]);
	}
}
