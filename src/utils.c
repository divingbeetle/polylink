#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "../include/utils.h"

long pow_int(int base, int exp)
{
    long res = 1;
    for (int i = 0; i < exp; i++)
    {
        res *= base;
    }
    return res;
}

bool get_int_input(int *number, enum int_input_mode mode)
{
    // Arbitrary but enough size for 32 bit integer
    char buffer[50];

    // Get input
    if (!fgets(buffer, sizeof(buffer), stdin))
    {
        return false;
    }

    // Check if input is too long
    if (buffer[strlen(buffer) - 1] != '\n')
    {
        printf("\nInvalid input: ");
        printf("input too long\n");
        // Flush stdin
        while (getchar() != '\n');
        return false;
    }

    // Convert to int
    char *endptr;
    long value = strtol(buffer, &endptr, 10);

    // Check for conversion errors
    if (endptr == buffer || *endptr != '\n')
    {
        printf("Invalid input: ");
        printf("Not a valid integer\n");
        return false;
    }

    // Check for out of range
    if (value < INT_MIN || value > INT_MAX)
    {
        printf("Invalid input: ");
        printf("Out of range\n");
        return false;
    }

    // Check for positive only
    if (mode == POSITIVE_ONLY && value <= 0)
    {
        printf("Invalid input: ");
        printf("Must be positive\n");
        return false;
    }

    *number = (int)value;
    return true;
}
