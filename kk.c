#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "maxheap.h"

uint64_t kkAlg(uint64_t* a, int n);
void regenInput(char* filename, int n);


int main(int argc, char *argv[]){

	if (argc != 2){
		printf("Input Argument: ./kk inputfile");
	}
	
	int n = 5; // global for # of numbers in array 

	//regenInput(argv[1], n);  //toggle to rewrite file

	uint64_t* a = malloc(sizeof(uint64_t) * n); 	// array with numbers 

	// Read File 
	FILE *readfile = fopen(argv[1], "r");

	if (readfile == NULL) {
		printf("Read error\n");
		return 0;
	}

	for (int i = 0; i < n; i++){
		fscanf(readfile, "%lli", &a[i]);
	}

	/*
	// print array
	for (int i = 0; i < n; i++){
		printf("%lli ", a[i]);
	}
	*/

	fclose(readfile);

	uint64_t residue = kkAlg(a, n);
	printf("Residue (KK Alg): %lli\n", residue);
	// kk implementation: 

	free(a);

	return 0;
}

//------------------------------- HELPER FUNCS

// KK algorithm 
uint64_t kkAlg(uint64_t* a, int n) {
 	// intialize heap
    Heap* heap = initHeap();

    // insert elements of array into heap
    for (int i = 0; i < n; i++) {
        insert(heap, a[i]);
        printf("Inserted value: %lli\n",a[i]);
    }

    // While there is more than 1 element in the heap
    while (heapSize(heap) > 1) {
    	uint64_t grea = extractMax(heap);
    	uint64_t less = extractMax(heap);
    	//printf("Greater: %lli\n", grea);
    	//printf("Lesser: %lli\n", less);
        insert(heap, grea - less);

        //insert(heap, extractMax(heap) - extractMax(heap));
    }
    // final value is the residue
    uint64_t res = extractMax(heap);

    heapFree(heap); // last root is popped so we free the heap
    return res;
}

// regenerates inputfile numbers (specified by ./kk inputfile)
void regenInput(char* filename, int n){
	// Open the file for writing
	FILE *file = fopen(filename, "w");

	srand(time(NULL));
	for (int i = 0; i < n; ++i){
		uint64_t val = pow(10, 12) * rand()/RAND_MAX;
		while (val == 0){
			uint64_t val = pow(10, 12) * rand()/RAND_MAX;
		}
		fprintf(file, "%lli", val);
		fprintf(file, "\n"); 
	}
	
	fclose(file);
}




