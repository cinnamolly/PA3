#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

//--------------------------- TYPES

typedef struct Heap {
    uint64_t* heapArray;    // points to array of values
    int heapCount;          // keeps track of # of values in our heap
} Heap;

//--------------------------- HEADERS

Heap* initHeap();
void insert(Heap* heap, uint64_t a);
uint64_t extractMax(Heap* heap);
void maxHeapify(Heap* heap, int N);
void swap(uint64_t* first, uint64_t* second);
void printHeap(Heap* heap);
int leftChild(int i);
int rightChild(int i);
int parent(int i);
int heapSize(Heap* heap);
void heapFree(Heap* heap);
