#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define INITCAP 16

void printline(char *line, int size, long cline){
	printf("%08lx  ",cline );
	for(int i=0;i<size;i++){
		if(i==INITCAP/2)
			printf("  ");
		printf("%02x ",line[i] );
	}
	if(size<INITCAP)
		for(int i=0;i<(INITCAP-size)*3+2;i++)
			printf(" ");
	printf("|");
	for (int i = 0; i < size; ++i){
		if(line[i]=='\n'){
			printf(".");
			i++;
		}
		printf("%c",line[i] );
	}
	printf("|\n");
}

void hexdump(FILE *fp){
	char *line = (char *)malloc(INITCAP);
	int size;
	long cline=0;
	while(!feof(fp)){
		for(size=0;size<INITCAP;size++){
			line[size]=fgetc(fp);
				if(feof(fp))
					break;
		}
		printline(line,size,cline);
		cline+=16;
	}
		
}

int main(int argc, char const *argv[])
{
	FILE *fp=NULL;
	if(argc > 1)
		for(int i=1;i<argc;i++){
			fp=fopen(argv[i],"r");
			hexdump(fp);
		}
	if(fp==NULL){
		printf("ERROR WHILE READING FILE!!!\n");
		return 1;
	}
	return 0;
}