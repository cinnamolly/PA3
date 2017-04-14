
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "maxheap.h"

//--------------------------- HEADERS
// initialize a new heap 
Heap* initHeap();
void insert(Heap* heap, uint64_t a);
uint64_t extractMax(Heap* heap);
void maxHeapify(Heap* heap, int N);
void swap(uint64_t* first, uint64_t* second);
void printHeap(Heap* heap);
/*
int leftChild(int i);
int rightChild(int i);
int parent(int i);
*/

int leftChild(Heap* heap, int i);
int rightChild(Heap* heap, int i);
int parent(Heap* heap, int i);

int heapSize(Heap* heap);
void heapFree(Heap* heap);

//--------------------------- FUNCTIONS
// initialize a new heap
Heap* initHeap(){
	Heap* heap = (struct Heap*) malloc(sizeof(struct Heap));
    heap->heapArray = malloc(101 * sizeof(uint64_t));
    heap->heapCount = 0;    
    return heap; 
}

// Insert a into heap, rearrange if necessary 
void insert(Heap* heap, uint64_t a){
	// insert at next available index 
	heap->heapArray[heap->heapCount] = a;

	int index = heap->heapCount;
	heap->heapCount++;

	// swap to correct heap position
	while (index != 0 && heap->heapArray[parent(heap, index)] < heap->heapArray[index]) {
		//printf("Parent: %lli, Child: %lli\n", heap->heapArray[parent(index)],heap->heapArray[index]);
		swap(&(heap->heapArray[parent(heap, index)]), &(heap->heapArray[index]));
		//printf("Post Swap - Parent: %lli, Child: %lli\n", heap->heapArray[parent(index)],heap->heapArray[index]);
		index = parent(heap, index);
	}

	printf("Heap Array Ins (After Swap): ");
	for (int i = 0; i < (heap->heapCount); i++){
		printf("%lli ", heap->heapArray[i]);
	}
	printf("\n");
}

// Pop max off the heap
uint64_t extractMax(Heap* heap) {

	if (heap->heapCount < 1) {
    	printf("Not enough elements in heap for extractMax");
    }
	uint64_t max_val = heap->heapArray[0];  // max val should be the first element
	
	heap->heapCount--;
	heap->heapArray[0] = heap->heapArray[heap->heapCount];

	maxHeapify(heap, 0);

	printf("Popped Value: %lli\n", max_val);

	return max_val;
}

// N must be root of a Max-heap
void maxHeapify(Heap* heap, int N) {
	// N represents a value in the heap 
	int right = rightChild(heap, N);
    int left = leftChild(heap, N);
    int largest = N;
    
    if (heap->heapArray[left] > heap->heapArray[largest] && left != -1) {
        largest = left;
    } 
    if (heap->heapArray[right] > heap->heapArray[largest] && right != -1) {
        largest = right;
    }

    // swap if necessary and call maxheapify
    if (largest != N) {
        swap(&(heap->heapArray[N]), &(heap->heapArray[largest]));
        maxHeapify(heap, largest);
    }
}

// swap values in the heap (so much easier than PA1 omg)
void swap(uint64_t* first, uint64_t* second){
	uint64_t temp = *first;
	*first = *second;
	*second = temp;
}

// print the heap 
void printHeap(Heap* heap) {
    printf("Heap: ");
    for (int i = 0; i < heap->heapCount; i++) {
        printf("%lli ", heap->heapArray[i]);
    }
    printf("\n");
}

// returns the index of the left/right child and parent given node at index i
int leftChild(Heap* heap, int i) {
	return (2*i+1 <= heap->heapCount) ? 2*i+1 : -1;
}
int rightChild(Heap* heap, int i) {
	return (2*i+2 <= heap->heapCount) ? 2*i+2 : -1;
}
int parent(Heap* heap, int i) {
	return (i==0) ? -1 : (i-1)/2;
}

int heapSize(Heap* heap) {
	return heap->heapCount;
}

void heapFree(Heap* heap) {
	free(heap->heapArray);
	free(heap);
}

