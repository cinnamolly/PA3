typedef struct heap_node {
    // vertex number of the endpoint u of edge (v, u) 
    // where v is element in cut S. and U is in V-S
    int vertex_number;
    double value;
} heap_node;

typedef struct Heap {
    heap_node* heapArray;
    int heapCount;
} Heap;

// HEAP helper functions; left, right are different than notes, bc starting at 0 index instead of 1;
int leftChild(int i) {
    int left_index = 2*i + 1;
    return left_index;
}

int rightChild(int i) {
    int right_index = 2*i + 2;
    return right_index;
}

int parent(int i) {
    return i/2;
}

void printHeap(Heap* heap) {
    printf("Heap");
    for (int i = 0; i < heap->heapCount; i++) {
        printf("(vertex %i, value %f) ",heap->heapArray[i].vertex_number, heap->heapArray[i].value);
    }
    printf("\n");
}

// given a pointer to heap node, prints contents
void printNode(heap_node* node) {
    printf("vertex number: %i, value: %f\n", 
        node->vertex_number, node->value);
}

// pass in heap and test if values are correctly sorted by checking heap property
bool validHeap(Heap* heap) {
    for (int i = 0; i < heap->heapCount; i++) {
        if (heap->heapArray[parent(i)].value > heap->heapArray[i].value) {
            return false;
        }
    }
    return true;
}

void swap(Heap* heap, int* indexArray, int a, int b) {
    heap_node* temp = (struct heap_node*) malloc(sizeof(struct heap_node));
    

    int first_vertex = heap->heapArray[a].vertex_number;
    int second_vertex = heap->heapArray[b].vertex_number;

    int temp_index = indexArray[first_vertex];
    
    indexArray[first_vertex] = indexArray[second_vertex];
    indexArray[second_vertex] = temp_index;
    
    temp->vertex_number = heap->heapArray[a].vertex_number;
    temp->value = heap->heapArray[a].value;
    
    heap->heapArray[a] = heap->heapArray[b];
    heap->heapArray[b].vertex_number = temp->vertex_number;
    heap->heapArray[b].value = temp->value;
    free(temp);
}

// N must be root of a Min-Heap
void minHeapify(Heap* heap, int* indexArray, int N) {
    
    int left = leftChild(N);
    int right = rightChild(N);
    int largest;
    
    // check to make sure if suppose to be >= or just > by looking at heapCount
    if (heap->heapCount > left && heap->heapArray[left].value < heap->heapArray[N].value) {
        largest = left;
    } 
    else {
        largest = N;
    }
    if (heap->heapCount > right && heap->heapArray[right].value < heap->heapArray[largest].value) {
        largest = right;
    }
    if (largest != N) {
        swap(heap, indexArray, N, largest);
        minHeapify(heap, indexArray, largest);
    }
}

// Insert updates("decreases") value of node in heap
void insert(int v, double new_weightval, int* indexArray, Heap* heap) {
    // N is the index position v is in the heap; -1 means hasn't been inserted
    
    int N = indexArray[v];
    
    if (N == -1) {
        heap->heapCount++;   
        N = heap->heapCount - 1;
        heap->heapArray[N].vertex_number = v;
        heap->heapArray[N].value = new_weightval;
        indexArray[v] = N;
    } 
    else {
        heap->heapArray[N].value = new_weightval;
    }
    

    while (N > 0 && heap->heapArray[parent(N)].value > heap->heapArray[N].value) {
        int parent_index = parent(N);

        swap(heap, indexArray, N, parent_index);

        N = parent_index;
    }
    return;
}

int extractMin(Heap* heap, int* indexArray) {
    if (heap->heapCount < 1) {
        printf("extractMin, Heap underflow");
    }
    // printf("heap before minheapify \n");
    // printHeap(heap);
    
    int temp_index = heap->heapArray[0].vertex_number;
    int v = temp_index;   
    // clear the vertex from heap index array since the vertex is not in the heap anymore
    indexArray[v] = -1;

    heap->heapArray[0] = heap->heapArray[heap->heapCount -1];

    int last_vertex = heap->heapArray[heap->heapCount - 1].vertex_number;

    indexArray[last_vertex] = 0;

    if (heap->heapCount == 1) {
        indexArray[last_vertex] = -1;
    }

    heap->heapCount--;

    minHeapify(heap, indexArray, 0);

    return v;
}
