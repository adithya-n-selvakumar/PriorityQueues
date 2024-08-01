// data_structures.h
// Adithya N. Selvakumar, anselvak, 1234965019

#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

// Structure to represent an element in the heap
typedef struct TAG_ELEMENT {
    double key;  // The key value based on which the heap is organized
} ELEMENT;

// Structure to represent the heap itself
typedef struct TAG_HEAP {
    int capacity;  // Maximum number of elements the heap can hold
    int size;      // Current number of elements in the heap
    ELEMENT **H;   // Pointer to an array of pointers to ELEMENT
} HEAP;

#endif // DATA_STRUCTURES_H