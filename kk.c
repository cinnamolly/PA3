#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

typedef struct heap_node {
	// only need the value 
    unsigned long long value;
} heap_node;

typedef struct Heap {
    heap_node* heapArray;
    int heapCount; //wtf does this keep track of? 
} Heap;

int main(int argc, char *argv[]){
	//int a[100];
	//int index = 0;

	if (argc != 2){
		printf("Input Argument: ./kk inputfile");
	}
	FILE *file = fopen(argv[1], "w");
	//char line [128];

	srand(time(NULL));
	for (int i = 0; i < 100; ++i){
		unsigned long long int val = pow(10, 12) * rand()/RAND_MAX;
		while (val == 0){
			unsigned long long int val = pow(10, 12) * rand()/RAND_MAX;
		}
		fprintf(file, "%lli", val);
		fprintf(file, "\n"); 
	}
	
	fclose(file);
}

//int karmarkar()