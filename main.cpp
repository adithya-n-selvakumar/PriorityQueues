// main.cpp
// Adithya N. Selvakumar, anselvak, 1234965019

#include <iostream>
#include <cstdlib>
#include "heap.h"
#include "util.h"

int main(int argc, char *argv[]) {
    // Ensure exactly four arguments are provided
    if (argc != 4) {
        std::cerr << "Usage: ./PJ2 flag <FileI> <FileO>\n"
                  << "flag is in {0, 1, 2, 3}\n"
                  << "<FileI> is the input file\n"
                  << "<FileO> is the output file\n";
        return EXIT_FAILURE;
    }

    int flag;
    try {
        flag = std::stoi(argv[1]);  // Convert argv[1] to an integer safely
    } catch (const std::invalid_argument& ia) {
        std::cerr << "Invalid flag value. Must be a number between 0 and 3.\n";
        return EXIT_FAILURE;
    }

    // Check if the flag value is within the expected range
    if (flag < 0 || flag > 3) {
        std::cerr << "Invalid flag value. Must be 0, 1, 2, or 3.\n";
        return EXIT_FAILURE;
    }

    HEAP *heap = nullptr;  // Initialize heap pointer as nullptr

    processCommands(heap, argv);  // Process commands from standard input

    return 0;  // Return success upon completion of command processing
}
