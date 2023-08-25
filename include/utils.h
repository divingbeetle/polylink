#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

// Flag for get_int_input() to indicate range of integers to allow 
enum int_input_mode
{
    ALLOW_ALL,      // Allow all integers
    POSITIVE_ONLY,  // Allow only positive integers
};

// Function prototypes

// Power function for integers
long pow_int(int base, int exp);

// Gets a single integer from user
// Returns true if successful
bool get_int_input(int *number, enum int_input_mode mode);

#endif // UTILS_H