#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "maxheap.h"

uint64_t kkAlg(uint64_t* a, int n);

int* randSolution_RandomMove(uint64_t* a, int n);
int* randNeighbor_RandomMove(int* soln, int n);
uint64_t residue_RandomMove(int* soln, uint64_t* a, int n);

uint64_t residue_Prepartition(uint64_t* a, int n);

int* repeated_random(uint64_t* a, int n);
int* hill_climbing(uint64_t* a, int n);

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
	
	int* randSoln = randSolution_RandomMove(a,n);
	uint64_t residue_random = residue_RandomMove(randSoln, a, n);
	printf("Residue (Random Move): %lli\n", residue_random);


	uint64_t residue_pre = residue_Prepartition(a, n);
	printf("Residue (Prepartition): %lli\n", residue_pre);

	int* random = repeated_random(a, n);
	uint64_t residue_RandomMove_RepeatedRandom = residue_RandomMove(random, a, n);
	printf("Residue (Random Move - Repeated Random): %lli\n", residue_RandomMove_RepeatedRandom);

	int* hill = hill_climbing(a, n);

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
    	printf("Greater: %lli\n", grea);
    	printf("Lesser: %lli\n", less);
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

int* randSolution_RandomMove(uint64_t* a, int n)
{
	int r;
	uint64_t group1 = 0;
	uint64_t group2 = 0;
	int* solution = malloc(sizeof(uint64_t) * n);
	for(int x = 0; x < n; x++){
		//srand(time(NULL));
		r = rand()%2;
		//printf("Random: %d\n", r);
		if(r == 0){
			group1 += a[x];
			solution[x] = 1;
			printf("%d,", solution[x]);
		}
		else{
			group2 += a[x];
			solution[x] = -1;
			printf("%d,", solution[x]);
		}
	}
	printf("\n");
	return solution;
}

//neighbor flipping not working
int* randNeighbor_RandomMove(int* soln, int n){
	//srand(time(NULL));
	int r1 = rand()%n;
	int r2 = rand()%n;
	double prob = (double)rand()/RAND_MAX*1.0;
	printf("Prob: %f\n", prob);
	while(r1 == r2){
		r1 = rand()%n;
		r2 = rand()%n;
	}
	printf("Neighbor r1: %d\n", r1);
	printf("Neighbor r2: %d\n", r2);
	printf("Old r1: %d\n", soln[r1]);
	soln[r1] = -1*soln[r1];
	printf("New r1: %d\n", soln[r1]);
	if(prob >= .5){
		printf("Old r2: %d\n", soln[r2]);
		soln[r2] = -1*soln[r2];
		printf("New r2: %d\n", soln[r2]);
	}
	return soln;
}

uint64_t residue_RandomMove(int* soln, uint64_t* a, int n)
{
	uint64_t resi = 0;
	for(int y = 0; y<n; y++){
		resi+= soln[y]*a[y];
	}
	return abs(resi);
}

uint64_t residue_Prepartition(uint64_t* a, int n){
	srand(time(NULL));
	int r;
	uint64_t resi;

	// allocated and zero initiates
	uint64_t* alt = calloc(n, sizeof(uint64_t));
	uint64_t* p = calloc(n, sizeof(uint64_t));

	printf("P: ");
	for(int x = 0; x < n; x++){
		r = rand() % n;
		p[x] = r;
		printf("%lli, ", p[x]);
	}
	for(int y = 0; y < n; y++){
		uint64_t index = p[y];
		uint64_t val = a[y];
		alt[index] = alt[index] + val;
	}
	printf("\n");
	printf("A: ");
	for(int z = 0; z<n; z++){
		printf("%lli, ", a[z]);
	}
	printf("\n");
	free(p);

	printf("A': ");
	for (int i = 0; i < n; i++){
		printf("%lli ", alt[i]);
	}
	printf("\n");
	// for some reason, generating HUGE numbers sometimes
	resi = kkAlg(alt, n);
	free(alt);
	return resi;
}

int* repeated_random(uint64_t* a, int n){
	//printf("A\n");
	int* randomSolutionA = randSolution_RandomMove(a,n);
	for(int x = 0; x < n; x++){
		//printf("B\n");
		int* randomSolutionB = randSolution_RandomMove(a,n);
		uint64_t residueA = residue_RandomMove(randomSolutionA, a, n);
		uint64_t residueB = residue_RandomMove(randomSolutionB, a, n);
		//printf("Resiude A: %lli\n", residueA);
		//printf("Resiude B: %lli\n", residueB);
		if (residueB < residueA){
			randomSolutionA = randomSolutionB;
		}
	}
	return randomSolutionA;
}

int* hill_climbing(uint64_t* a, int n){
	int* randomSolution = randSolution_RandomMove(a,n);
	for(int x = 0; x < n; x++){
		int* randomNeighbor = randNeighbor_RandomMove(randomSolution, n);
		uint64_t residueA = residue_RandomMove(randomSolution, a, n);
		uint64_t residueB = residue_RandomMove(randomNeighbor, a, n);
		printf("Resiude A: %lli\n", residueA);
		printf("Resiude B: %lli\n", residueB);
		if (residueB < residueA){
			randomSolution = randomNeighbor;
		}
	}
	return randomSolution;
}



