// util.cpp
// Implementation of utility functions for command handling
// Adithya N. Selvakumar, anselvak, 1234965019

#include "util.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>  // For std::fixed and std::setprecision

void processCommands(HEAP *heap, char *argv[]) {
    std::string command;
    int flag = std::stoi(argv[1]); // Assuming argv[1] is the flag argument

    while (std::cin >> command) {
        if (command == "Stop") {
	    std::cout << "Instruction: " << command << "\n"; // Reflect command as instruction
            // Remove the "Stopping..." output entirely
            break;
        } else if (command == "Init") {
            int capacity;
            std::cin >> capacity;
            heap = InitHeap(capacity);
            if (!heap) {
                std::cerr << "Error: Initialization of heap failed\n";
            } else {
                std::cout << "Instruction: Init " << capacity << std::endl;
            }
        } else if (command == "Print") {
            if (heap == nullptr) {
                std::cerr << "Error: Heap not initialized.\n";
            } else {
		std::cout << "Instruction: " << command << "\n"; // Reflect command as instruction
		PrintHeap(heap, flag); // This function must be edited to output elements in new lines
            }
        } else if (command == "Write") {
            if (heap == nullptr) {
                std::cerr << "Error: Heap not initialized.\n";
            } else {
                WriteHeap(heap, argv[3]);
		std::cout << "Instruction: " << command << "\n"; // Reflect command as instruction
            }
        } else if (command == "Read") {
            if (heap == nullptr) {
                std::cerr << "Error: Heap not initialized.\n";
            } else {
		std::cout << "Instruction: " << command << "\n"; // Reflect command as instruction
                ReadHeap(heap, argv[2], flag);
            }
        } else if (command == "Insert") {
            double key;
            std::cin >> key;
            ELEMENT *element = new ELEMENT{key}; // Assume ELEMENT constructor
            if (heap == nullptr) {
            	std::cerr << "Error: Heap not initialized.\n";
            } else {
                std::cout << "Instruction: " << command << " " << std::fixed << std::setprecision(6) << key << std::endl;
		Insert(heap, element, flag);
            }
        } else if (command == "ExtractMin") {
            if (heap == nullptr) {
                std::cerr << "Error: Heap not initialized.\n";
            } else {
                std::cout << "Instruction: " << command << "\n"; // Always print the instruction
                ELEMENT *min = ExtractMin(heap, flag);
                // The above call will handle all necessary printing based on the flag.
            }
        } else if (command == "DecreaseKey") {
    	    int index;
    	    double newKey;
    	    std::cin >> index >> newKey;
    	    std::cout << "Instruction: DecreaseKey " << index << " " << std::fixed << std::setprecision(6) << newKey << std::endl;
    	    if (heap == nullptr) {
        	std::cout << "Error: Heap not initialized.\n" << std::endl;
    	    } else if (index < 1 || index > heap->size) {
        	std::cout << "Error: invalid call to DecreaseKey\n" << std::endl;
    	    } else if (newKey >= heap->H[index - 1]->key) {
        	std::cout << "Error: new key is greater than current key\n" << std::endl;
    	    } else {
        	DecreaseKey(heap, index, newKey);
    	    }
	} else {
            std::cout << "Invalid command: " << command << std::endl;
        }
    }
}
