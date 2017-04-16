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
int* randNeighbor_Prepartition(int* p, int n);
uint64_t residue_Prepartition(int* p, uint64_t* a, int n);

//if flag = 0, random move; flag = 1, prepartition
int* repeated_random(uint64_t* a, int n, int flag);
int* hill_climbing(uint64_t* a, int n, int flag);
int* sim_annealing(uint64_t* a, int n, int flag);

double T(int k);

void regenInput(char* filename, int n);


int main(int argc, char *argv[]){

	// clear result files 
	FILE* f = fopen("residues.csv", "w");
	FILE* f0 = fopen("kkresults.csv", "w");
	FILE* f2 = fopen("runtimes.csv", "w");
	fclose(f);
	fclose(f0);
	fclose(f2);

	// 100 iterations
	for(int w = 0; w < 15; w++)
	{
		if (argc != 2){
			printf("Input Argument: ./kk inputfile");
		}
		
		int n = 100; // global for # of numbers in array 

		regenInput(argv[1], n);  //toggle to rewrite file

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

		fclose(readfile);

		struct timeval progtime[17];
		gettimeofday(&progtime[0], NULL);
		uint64_t residueKK = kkAlg(a, n);
		printf("Residue (KK Alg): %lli\n", residueKK);
		gettimeofday(&progtime[1], NULL);

		double time_KK = (double)((progtime[1].tv_sec - progtime[0].tv_sec) * 1000000)
				+ (progtime[1].tv_usec - progtime[0].tv_usec);

		FILE* f0 = fopen("kkresults.csv", "a");
	    if (f0 == NULL) {
	        printf("Error opening file\n");
	    }
	    fprintf(f0, "%lli,%f\n", residueKK, time_KK);
	    
	    fclose(f0);
		
		int iterations = 25;
		uint64_t resd_RM[iterations];
		double time_RM[iterations];
		uint64_t resd_PP[iterations];
		double time_PP[iterations];
		uint64_t resd_repeatRand_RM[iterations];
		double time_repeatRand_RM[iterations];
		uint64_t resd_repeatRand_PP[iterations];
		double time_repeatRand_PP[iterations];
		uint64_t resd_hill_RM[iterations];
		double time_hill_RM[iterations];
		uint64_t resd_hill_PP[iterations];
		double time_hill_PP[iterations];
		uint64_t resd_sim_RM[iterations];
		double time_sim_RM[iterations];
		uint64_t resd_sim_PP[iterations];
		double time_sim_PP[iterations];

		printf("residue 1\n");
		for(int i = 0; i < iterations; i++)
		{
			gettimeofday(&progtime[2], NULL);
			int* randSoln = randSolution_RandomMove(a,n);
			uint64_t residue_random = residue_RandomMove(randSoln, a, n);
			//printf("Residue (Random Move): %lli\n", residue_random);
			gettimeofday(&progtime[3], NULL);
			resd_RM[i] = residue_random; 
			time_RM[i] = (double)((progtime[3].tv_sec - progtime[2].tv_sec) * 1000000)
				+ (progtime[3].tv_usec - progtime[2].tv_usec);
			free(randSoln);
		}
		
		printf("residue 2\n");
		for(int i = 0; i < iterations; i++)
		{
			gettimeofday(&progtime[4], NULL);
			int* randPrepartition = randSolution_Prepartition(a,n);
			uint64_t residue_pre = residue_Prepartition(randPrepartition, a, n);
			//printf("Residue (Prepartition): %lli\n", residue_pre);
			gettimeofday(&progtime[5], NULL);
			resd_PP[i] = residue_pre;
			time_PP[i] = (double)((progtime[5].tv_sec - progtime[4].tv_sec) * 1000000)
				+ (progtime[5].tv_usec - progtime[4].tv_usec);
			free(randPrepartition);
		}
		
		printf("residue 3\n");
		for(int i = 0; i < iterations; i++)
		{
			gettimeofday(&progtime[5], NULL);
			int* random = repeated_random(a, n, 0);
			uint64_t residue_RandomMove_RepeatedRandom = residue_RandomMove(random, a, n);
			//printf("Residue (Random Move - Repeated Random): %lli\n", residue_RandomMove_RepeatedRandom);
			gettimeofday(&progtime[6], NULL);
			resd_repeatRand_RM[i] = residue_RandomMove_RepeatedRandom;
			time_repeatRand_RM[i] = (double)((progtime[6].tv_sec - progtime[5].tv_sec) * 1000000)
				+ (progtime[6].tv_usec - progtime[5].tv_usec);
			free(random);
		}
		
		printf("residue 4\n");
		for(int i = 0; i < iterations; i++)
		{
			gettimeofday(&progtime[7], NULL);
			int* random2 = repeated_random(a, n, 1);
			uint64_t residue_Prepartition_RepeatedRandom = residue_Prepartition(random2, a, n);
			//printf("Residue (Prepartition - Repeated Random): %lli\n", residue_Prepartition_RepeatedRandom);
			gettimeofday(&progtime[8], NULL);
			resd_repeatRand_PP[i] = residue_Prepartition_RepeatedRandom;
			time_repeatRand_PP[i] = (double)((progtime[8].tv_sec - progtime[7].tv_sec) * 1000000)
				+ (progtime[8].tv_usec - progtime[7].tv_usec);
			free(random2);
		}
		
		printf("residue 5\n");
		for(int i = 0; i < iterations; i++)
		{
			gettimeofday(&progtime[9], NULL);
			int* hill = hill_climbing(a, n, 0);
			uint64_t residue_RandomMove_HillClimbing = residue_RandomMove(hill, a, n);
			//printf("Residue (Random Move - Hill Climbing): %lli\n", residue_RandomMove_HillClimbing);
			gettimeofday(&progtime[10], NULL);
			resd_hill_RM[i] = residue_RandomMove_HillClimbing;
			time_hill_RM[i] = (double)((progtime[10].tv_sec - progtime[9].tv_sec) * 1000000)
				+ (progtime[10].tv_usec - progtime[9].tv_usec);
			free(hill);
		}
		
		printf("residue 6\n");
		for(int i = 0; i < iterations; i++){
			gettimeofday(&progtime[11], NULL);
			int* hill2 = hill_climbing(a, n, 1);
			uint64_t residue_Prepartition_HillClimbing = residue_Prepartition(hill2, a, n);
			//printf("Residue (Prepartition - Hill Climbing): %lli\n", residue_Prepartition_HillClimbing);
			gettimeofday(&progtime[12], NULL);
			resd_hill_PP[i] = residue_Prepartition_HillClimbing;
			time_hill_PP[i] = (double)((progtime[12].tv_sec - progtime[11].tv_sec) * 1000000)
				+ (progtime[12].tv_usec - progtime[11].tv_usec);
			free(hill2);
		}
		
		printf("residue 7\n");
		for(int i = 0; i < iterations; i++){
			gettimeofday(&progtime[13], NULL);
			int* anneal1 = sim_annealing(a, n, 0);
			uint64_t residue_RandomMove_simanneal = residue_RandomMove(anneal1, a, n);
			//printf("Residue (Random Move - Simulated Annealing): %lli\n", residue_RandomMove_simanneal);
			gettimeofday(&progtime[14], NULL);
			resd_sim_RM[i] = residue_RandomMove_simanneal;
			time_sim_RM[i] = (double)((progtime[14].tv_sec - progtime[13].tv_sec) * 1000000)
				+ (progtime[14].tv_usec - progtime[13].tv_usec);
			free(anneal1);
		}
		
		printf("residue 8\n");
		for(int i = 0; i < iterations; i++){
			gettimeofday(&progtime[15], NULL);
			int* anneal2 = sim_annealing(a, n, 1);
			uint64_t residue_Prepartition_simanneal = residue_Prepartition(anneal2, a, n);
			//printf("Residue (Prepartition- Simulated Annealing): %lli\n", residue_Prepartition_simanneal);
			gettimeofday(&progtime[16], NULL);
			resd_sim_PP[i] = residue_Prepartition_simanneal;
			time_sim_PP[i] = (double)((progtime[16].tv_sec - progtime[15].tv_sec) * 1000000)
				+ (progtime[16].tv_usec - progtime[15].tv_usec);
			free(anneal2);
		}
		
	    FILE* f = fopen("residues.csv", "a");
	    if (f == NULL) {
	        printf("Error opening file\n");
	    }
	    for (int i = 0; i < iterations; i++) {
	    	fprintf(f, "%lld,%lld,%lld,%lld,%lld,%lld,%lld,%lld\n", resd_RM[i], resd_PP[i], 
	    		resd_repeatRand_RM[i], resd_repeatRand_PP[i], resd_hill_RM[i], resd_hill_PP[i], 
	    		resd_sim_RM[i], resd_sim_PP[i]);
	    }

	    fclose(f);

	    FILE* f2 = fopen("runtimes.csv", "a");
	    if (f2 == NULL) {
	        printf("Error opening file\n");
	    }
		for (int i = 0; i < iterations; i++) {
	    	fprintf(f2, "%f,%f,%f,%f,%f,%f,%f,%f\n", time_RM[i], time_PP[i], 
	    		time_repeatRand_RM[i], time_repeatRand_PP[i], time_hill_RM[i], 
	    		time_hill_PP[i], time_sim_RM[i], time_sim_PP[i]);
		}

	    fclose(f2);
		free(a);
	}

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
        //printf("Inserted value: %lli\n",a[i]);
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
		}
		else{
			group2 += a[x];
			solution[x] = -1;
		}
	}
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
	while(r1 == r2){
		r1 = rand()%n;
		r2 = rand()%n;
	}

	solution[r1] = -1*solution[r1];
	if(prob >= .5){
		solution[r2] = -1*solution[r2];
	}
	return solution;
}

uint64_t residue_RandomMove(int* soln, uint64_t* a, int n)
{
	uint64_t resi = 0;
	for(int y = 0; y<n; y++){
		resi+= soln[y]*a[y];
	}
	return abs(resi);
}

int* randNeighbor_Prepartition(int* p, int n){
	//srand(time(NULL));
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

	for(int x = 0; x < n; x++){
		r = rand() % n;
		p[x] = r;
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
	uint64_t resi = kkAlg(alt, n);
	return abs(resi);
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

		double maybe = (double)rand() / RAND_MAX;

		if (residueB < residueA){
			randomSolution = randomNeighbor;
		}
		else if ((maybe) < (exp((-residueB-residueA)/T(x)))) {
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

		if (residueA < residueC){
			iprvSolution = randomSolution;
		}
	}
	return iprvSolution;
}

double T(int k){
	//k representes the iterations, which are passed in
	// High initial value for high initial acceptability
	double T_init = pow(10, 10);
	double a = 0.8;
	return pow(a,k/300)*T_init;
}








