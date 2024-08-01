// util.h
// Utility functions for handling commands from stdin
// Adithya N. Selvakumar, anselvak, 1234965019

#ifndef UTIL_H
#define UTIL_H

#include "heap.h"  // Include the heap structure and functions

// Processes commands from stdin and performs corresponding heap operations
void processCommands(HEAP *heap, char *argv[]);

#endif // UTIL_H