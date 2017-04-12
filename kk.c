#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	int a[100];
	int index = 0;
	FILE *file = fopen(argv[1], "r");
	char line [128];
	while (fgets(line, sizeof(line), file))
	{
		//NOTE: not handling 64 bit, only integers
		//loading array a with the input
		//fputs(line, stdout);
		int x = atoi(line);
		a[index] = x;
		index++;
	}
	fclose(file);
}

int karmarkar()