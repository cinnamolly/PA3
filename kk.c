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

int* randSolution_Prepartition(uint64_t* a, int n);
uint64_t residue_Prepartition(int* p, uint64_t* a, int n);
int* randNeighbor_Prepartition(int* p, int n);

//if flag = 0, random move; flag = 1, prepartition
int* repeated_random(uint64_t* a, int n, int flag);
int* hill_climbing(uint64_t* a, int n, int flag);
int* sim_annealing(uint64_t* a, int n, int flag);

double T(int k);

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

	int* randPrepartition = randSolution_Prepartition(a,n);
	uint64_t residue_pre = residue_Prepartition(randPrepartition, a, n);
	printf("Residue (Prepartition): %lli\n", residue_pre);

	int* random = repeated_random(a, n, 0);
	uint64_t residue_RandomMove_RepeatedRandom = residue_RandomMove(random, a, n);
	printf("Residue (Random Move - Repeated Random): %lli\n", residue_RandomMove_RepeatedRandom);

	int* hill = hill_climbing(a, n, 0);
	uint64_t residue_RandomMove_HillClimbing = residue_RandomMove(hill, a, n);
	printf("Residue (Random Move - Hill Climbing): %lli\n", residue_RandomMove_HillClimbing);

	int* annealing = sim_annealing(a, n, 0);
	uint64_t residue_RandomMove_simannel = residue_RandomMove(annealing, a, n);
	printf("Residue (Random Move - Simulated Annealing): %lli\n", residue_RandomMove_simannel);

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
	int* solution = malloc(sizeof(int) * n);
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
int* randNeighbor_RandomMove(int* input, int n){
	//srand(time(NULL));
	int* solution = malloc(sizeof(int) * n);
	for(int y = 0; y < n; y++){
		solution[y] = input[y];
	}
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
	printf("Old r1: %d\n", solution[r1]);
	solution[r1] = -1*solution[r1];
	printf("New r1: %d\n", solution[r1]);
	if(prob >= .5){
		printf("Old r2: %d\n", solution[r2]);
		solution[r2] = -1*solution[r2];
		printf("New r2: %d\n", solution[r2]);
	}
	return solution;
}



uint64_t residue_RandomMove(int* soln, uint64_t* a, int n)
{
	uint64_t resi = 0;
	for(int y = 0; y<n; y++){
		resi+= soln[y]*a[y];
	}
	return resi;
}

int* randNeighbor_Prepartition(int* p, int n){
	int* solution = malloc(sizeof(int) * n);
	for(int y = 0; y < n; y++){
		solution[y] = p[y];
	}
	int r1 = rand()%n;
	int r2 = rand()%n;
	int p_value = p[r1];
	while(p_value == r2){
		r1 = rand()%n;
		r2 = rand()%n;
		p_value = p[r1];
	}
	solution[r1] = r2;
	return solution;
}

int* randSolution_Prepartition(uint64_t* a, int n){
	srand(time(NULL));
	int r;
	// allocated and zero initiates
	int* p = calloc(n, sizeof(int));

	printf("P: ");
	for(int x = 0; x < n; x++){
		r = rand() % n;
		p[x] = r;
		printf("%d, ", p[x]);
	}
	return p;
}

uint64_t residue_Prepartition(int* p, uint64_t* a, int n){
	uint64_t* alt = calloc(n, sizeof(uint64_t));
	for(int y = 0; y < n; y++){
		uint64_t index = p[y];
		uint64_t val = a[y];
		alt[index] = alt[index] + val;
	}
	/*printf("\n");
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
	printf("\n");*/
	uint64_t resi = kkAlg(alt, n);
	return resi;
}

int* repeated_random(uint64_t* a, int n, int flag){
	//printf("A\n");
	int* randomSolutionA;
	if(flag == 0){
		randomSolutionA = randSolution_RandomMove(a,n);
	}
	else{
		randomSolutionA = randSolution_Prepartition(a,n);
	}
	for(int x = 0; x < n; x++){
		//printf("B\n");
		int* randomSolutionB;
		uint64_t residueA;
		uint64_t residueB;
		if(flag==0){
			randomSolutionB = randSolution_RandomMove(a,n);
			residueA = residue_RandomMove(randomSolutionA, a, n);
			residueB = residue_RandomMove(randomSolutionB, a, n);
		}
		else{
			randomSolutionB = randSolution_Prepartition(a,n);
			residueA = residue_Prepartition(randomSolutionA, a, n);
			residueB = residue_Prepartition(randomSolutionB, a, n);
		}
		
		//printf("Resiude A: %lli\n", residueA);
		//printf("Resiude B: %lli\n", residueB);
		if (residueB < residueA){
			randomSolutionA = randomSolutionB;
		}
	}
	return randomSolutionA;
}

int* hill_climbing(uint64_t* a, int n, int flag){
	int* randomSolution;
	if(flag == 0){
		randomSolution = randSolution_RandomMove(a,n);
	}
	else{
		randomSolution = randSolution_Prepartition(a,n);
	}
	for(int x = 0; x < n; x++){
		int* randomNeighbor;
		if(flag == 0){
			randomNeighbor = randNeighbor_RandomMove(randomSolution, n);
		}
		else{
			randomNeighbor = randNeighbor_Prepartition(randomSolution, n);
		}
		printf("printing neighbor\n");
		for(int y = 0; y < n; y++){
			printf("%d,", randomNeighbor[y]);
		}
		printf("\nprinting soln\n");
		for(int y = 0; y < n; y++){
			printf("%d,", randomSolution[y]);
		}
		uint64_t residueA;
		uint64_t residueB;
		if(flag ==0){
			residueA = residue_RandomMove(randomSolution, a, n);
			residueB = residue_RandomMove(randomNeighbor, a, n);
		}
		else{
			residueA = residue_Prepartition(randomSolution, a, n);
			residueB = residue_Prepartition(randomNeighbor, a, n);
		}
		printf("Residue A: %lli\n", residueA);
		printf("Residue B: %lli\n", residueB);
		if (residueB < residueA){
			randomSolution = randomNeighbor;
		}
	}
	return randomSolution;
}

int* sim_annealing(uint64_t* a, int n, int flag){
	int* randomSolution;
	if(flag == 0){
		randomSolution = randSolution_RandomMove(a,n);
	}
	else{
		randomSolution = randSolution_Prepartition(a,n);
	}
	int* iprvSolution = randomSolution; // S'' = S

	for(int x = 0; x < n; x++){
		int* randomNeighbor;   // S
		if(flag == 0){
			randomNeighbor = randNeighbor_RandomMove(randomSolution, n);
		}
		else{
			randomNeighbor = randNeighbor_Prepartition(randomSolution, n);
		}
		printf("printing neighbor\n");
		for(int y = 0; y < n; y++){
			printf("%d,", randomNeighbor[y]);
		}
		printf("\nprinting soln\n");
		for(int y = 0; y < n; y++){
			printf("%d,", randomSolution[y]);
		}

		uint64_t residueA;        // residue of solution
		uint64_t residueB;        // residue of neighbor
		uint64_t residueC;        // residue of improved solu
		if(flag ==0){
			residueA = residue_RandomMove(randomSolution, a, n);
			residueB = residue_RandomMove(randomNeighbor, a, n);
			residueC = residue_RandomMove(iprvSolution, a, n);
		}
		else{
			residueA = residue_Prepartition(randomSolution, a, n);
			residueB = residue_Prepartition(randomNeighbor, a, n);
			residueC = residue_Prepartition(iprvSolution, a, n);
		}
		printf("Residue A Step1: %lli\n", residueA);
		printf("Residue B Step1: %lli\n", residueB);
		printf("Residue C Step1: %lli\n", residueB);

		if (residueB < residueA){
			randomSolution = randomNeighbor;
		}
		else if (((double)rand() / RAND_MAX) < (exp((-residueB-residueA)/T(x)))) {
			randomSolution = randomNeighbor;
		}
		// get residues again in case anything changes
		if(flag == 0){
			residueA = residue_RandomMove(randomSolution, a, n);
			residueB = residue_RandomMove(randomNeighbor, a, n);
			residueC = residue_RandomMove(iprvSolution, a, n);
		}
		else{
			residueA = residue_Prepartition(randomSolution, a, n);
			residueB = residue_Prepartition(randomNeighbor, a, n);
			residueC = residue_Prepartition(iprvSolution, a, n);
		}

		if (residueC < residueA){
			iprvSolution = randomNeighbor;
		}
	}
	return iprvSolution;
}

// cooling schedule: Exp Multiplicative Cooling T_k = a^k * T_0
// Proposed by Kirkpatrick, Gelatt, and Vecchi (1983)
//http://what-when-how.com/artificial-intelligence/a-comparison-of-cooling-schedules-for-simulated-annealing-artificial-intelligence/
double T(int k){
	//k representes the iterations, which are passed in
	// High initial value for high initial acceptability
	double T_init = pow(10, 7);
	double a = 0.95;
	return pow(a,k)*T_init;
}

