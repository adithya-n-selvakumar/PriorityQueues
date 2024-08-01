// heap.cpp
// Implementation of min heap operations
// Adithya N. Selvakumar, anselvak, 1234965019

#include "heap.h"
#include <iostream>
#include <fstream>
#include <cstdlib>  // For std::exit and EXIT_FAILURE
#include <iomanip>  // For std::fixed and std::setprecision
#include <cmath>

int heapifyCallCount = 0;

// Function definition
int getHeapifyCallCount() {
    return heapifyCallCount;
}

// Helper functions to get the index of the parent, left child, and right child nodes
int parent(int i) {
    int nominalIndex = i + 1; 
    int nominalParent = nominalIndex / 2; 
    if (nominalParent > 0) {
	return nominalParent - 1;
    } else {
	return 0;
    }
}
int left(int i) { 
    int nominalIndex = i + 1; 
    int nominalLeft = 2 * nominalIndex; 
    if (nominalLeft > 0) {
	return nominalLeft - 1;
    } else {
	return 0;
    }
}
int right(int i) { 
    int nominalIndex = i + 1; 
    int nominalRight = 2 * nominalIndex + 1; 
    if (nominalRight > 0) {
	return nominalRight - 1;
    } else {
	return 0;
    }
}

HEAP *InitHeap(int capacity) {
    HEAP *heap = new HEAP;
    if (!heap) {
        std::cerr << "Error: Memory allocation for HEAP failed\n";
        return nullptr;
    }
    heap->H = new ELEMENT*[capacity];
    if (!heap->H) {
        std::cerr << "Error: Memory allocation for heap array failed\n";
        delete heap;
        return nullptr;
    }
    heap->capacity = capacity;
    heap->size = 0;
    return heap;
}

void PrintHeap(HEAP *heap, int flag) {
    std::cout << heap->size << std::endl; // Removed based on feedback
    if (!heap || heap->size == 0) {
        std::cerr << "Error: heap is NULL or empty" << std::endl;
        return;
    }
    std::cout << std::fixed << std::setprecision(6);  // Set precision for floating point
    for (int i = 0; i < heap->size; ++i) {
        std::cout << heap->H[i]->key;
        if (i < heap->size - 1) {
            std::cout << std::endl; // Ensuring each key is on a new line
        }
    }
    std::cout << std::endl; // Ensure newline after the last element
}


void ReadHeap(HEAP *heap, const char *filename, int flag) {

    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: cannot open file " << filename << std::endl;
        std::exit(EXIT_FAILURE);
    }

    if (heap == nullptr) {
        std::cerr << "Error: heap is NULL\n";
        return;
    }

    int count;
    file >> count;
    if (count > heap->capacity) {
        std::cerr << "Error: file contains more elements than heap capacity" << std::endl;
        file.close();
        std::exit(EXIT_FAILURE);
    }

    bool isMinHeap = true;
    double lastKey = std::numeric_limits<double>::lowest(); // Use numeric limits instead of INFINITY
    for (int i = 0; i < count; ++i) {
        double key;
        file >> key;
        ELEMENT *element = new ELEMENT;
        element->key = key;
        heap->H[i] = element;
        if (i > 0 && key < heap->H[parent(i)]->key) { // Corrected the logic to check min-heap property
            isMinHeap = false;
        }
    }
    heap->size = count;
    file.close();

    if (!isMinHeap) {
        if (flag == 2 || flag == 3) { // Check flag before printing
            std::cout << "Input array is NOT a MinHeap\n";
            std::cout << "Call BuildHeap\n";
        }
        BuildHeap(heap);
        if (flag == 2 || flag == 3) {
            std::cout << "Number of Heapify calls triggered by BuildHeap: " << getHeapifyCallCount() << std::endl;
        }
    }
}

void WriteHeap(HEAP *heap, const char *filename) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error: cannot open file " << filename << std::endl;
        std::exit(EXIT_FAILURE);
    }
    file << heap->size << std::endl;
    for (int i = 0; i < heap->size; ++i) {
        file << std::fixed << std::setprecision(6) << heap->H[i]->key << std::endl;
    }
    file.close();
}

void Heapify(HEAP *heap, int i) {
    heapifyCallCount++;
    int l = left(i);
    int r = right(i);
    int smallest = i;

    if (l < heap->size && heap->H[l]->key < heap->H[i]->key) {
        smallest = l;
    }
    if (r < heap->size && heap->H[r]->key < heap->H[smallest]->key) {
        smallest = r;
    }
    if (smallest != i) {
        std::swap(heap->H[i], heap->H[smallest]);
        Heapify(heap, smallest);
    }
}

void BuildHeap(HEAP *heap) {
    for (int i = heap->size / 2 - 1; i >= 0; i--) {
        Heapify(heap, i);
    }
}

ELEMENT *ExtractMin(HEAP *heap, int flag) {
    if (heap == nullptr) {
        std::cerr << "Error: Heap not initialized.\n";
        return nullptr;
    }

    if (heap->size < 1) {
        std::cerr << "Error: heap is empty" << std::endl;
        return nullptr;
    }

    ELEMENT *min = heap->H[0];
    heap->H[0] = heap->H[heap->size - 1];
    heap->size--;
    
    // Resetting heapifyCallCount before calling Heapify
    heapifyCallCount = 0;  
    Heapify(heap, 0);

    if (flag == 2 || flag == 3) {
        std::cout << "Element with key " << std::fixed << std::setprecision(6) << min->key << " extracted from the heap" << std::endl;
        std::cout << "Number of Heapify calls triggered by ExtractMin: " << heapifyCallCount << std::endl;
    } else {
        std::cout << "Element with key " << std::fixed << std::setprecision(6) << min->key << " extracted from the heap" << std::endl;
    }
    
    return min;
}


void Insert(HEAP *heap, ELEMENT *element, int flag) {
    if (heap->size == heap->capacity) {
        std::cerr << "Error: heap is full" << std::endl;
        return;
    }
    int i = heap->size++;
    heap->H[i] = element;
    while (i != 0 && heap->H[parent(i)]->key > heap->H[i]->key) {
        std::swap(heap->H[i], heap->H[parent(i)]);
        i = parent(i);
    }
    
    if (flag == 1 || flag == 3) {
        std::cout << "Element with key " << std::fixed << std::setprecision(6) << element->key << " inserted at location " << (i + 1) << " of the heap array" << std::endl;
    } else {
	std::cout << "Element with key " << std::fixed << std::setprecision(6) << element->key << " inserted into the heap" << std::endl;
    }
}

void DecreaseKey(HEAP *heap, int nominalIndex, double newKey) {
    if (heap == nullptr) {
        std::cout << "Error: Heap is NULL\n" << std::endl;
        return;
    }
    if (heap->size == 0) {
        std::cout << "Error: Heap is empty\n" << std::endl;
        return;
    }

    int realIndex = nominalIndex - 1;
    if (realIndex < 0 || realIndex >= heap->size) {
        std::cout << "Error: Index out of bounds\n" << std::endl;
        return;
    }
    if (newKey >= heap->H[realIndex]->key) {
        std::cout << "Error: New key is not smaller than current key\n" << std::endl;
        return;
    }

    //std::cout << "Updating key at index " << nominalIndex << " from " << heap->H[realIndex]->key << " to " << newKey << std::endl;
    heap->H[realIndex]->key = newKey;
    // Swim up
    int currentReal = realIndex;
    while (currentReal != 0 && heap->H[parent(currentReal)]->key > heap->H[currentReal]->key) {
        //std::cout << "Swapping " << heap->H[currentReal]->key << " with parent " << heap->H[parent(currentReal)]->key << std::endl;
        std::swap(heap->H[currentReal], heap->H[parent(currentReal)]);
        currentReal = parent(currentReal);
    }
}


