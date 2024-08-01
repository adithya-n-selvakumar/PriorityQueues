#ifndef HEAP_H
#define HEAP_H

#include "data_structures.h"  // Include the data structures for elements and heap

HEAP *InitHeap(int capacity);
void Heapify(HEAP *heap, int index);
void BuildHeap(HEAP *heap);
void Insert(HEAP *heap, ELEMENT *element, int flag);  // Include flag for output control
ELEMENT *ExtractMin(HEAP *heap, int flag);
void DecreaseKey(HEAP *heap, int index, double newKey);
void PrintHeap(HEAP *heap, int flag);  // Include flag for output control
void ReadHeap(HEAP *heap, const char *filename, int flag);
void WriteHeap(HEAP *heap, const char *filename);
int getHeapifyCallCount();


#endif // HEAP_H
