// Simple polynomial operations program
// Created to practice linked lists

#include <stdlib.h>
#include <stdio.h>
#include "../include/polynomial_operations.h"

// User options
// Keep it under 10 for compatibility with get_option_input()
enum options
{
    OPTION_EXIT,
    OPTION_INPUT,
    OPTION_ADD,
    OPTION_DELETE,
    OPTION_DIFF,
    OPTION_SUB,
    OPTIONS_COUNT // Always keep this at the end
};

// Option descriptions strings for display_options_menu()
// Corresponds to enum options
const char *options_str[OPTIONS_COUNT] =
    {
        "Exit Program",
        "Input polynomial",
        "Add a monomial to the polynomial",
        "Delete a monomial from the polynomial",
        "Differentiate current polynomial",
        "Substitute x for polynomial",
};

// Function prototypes

// Prints options menu
void display_options_menu(void);

// Gets a single digit option from user
// Returns option as enum options
// Assumes that min and max are single digits integers
enum options get_option_input(const char *prompt, int min, int max);

int main(void)
{
    struct poly_node *polynomial = NULL;

    enum options option;
    do
    {
        display_options_menu();    
        print_polynomial(polynomial);
        option = get_option_input("\nSelect a option: ", 0, OPTIONS_COUNT - 1);    
        switch (option) 
        {
            case OPTION_INPUT: 
                polynomial = input_polynomial(polynomial);
                break;
            case OPTION_ADD: 
                polynomial = add_monomial(polynomial);
                break;
            case OPTION_DELETE:
                polynomial = delete_monomial(polynomial);
                break;
            case OPTION_DIFF: 
                polynomial = differentiate_polynomial(polynomial);
                break;
            case OPTION_SUB: 
                substitute_polynomial(polynomial);
                break;
        }
    } 
    while (option != OPTION_EXIT);
    free_polynomial(polynomial);
}

enum options get_option_input(const char *prompt, int min, int max)
{
    while (1)
    {
        printf("%s", prompt);
        int option = getchar();
        if (option == '\n')
        {
                continue;
        }
        else if (option == EOF)
        {
                printf("Unexpected EOF\n");
                exit(0);
        }
        // Check if option is a single digit between min and max
        // Followed by a newline
        else if (option >= min + '0' && option <= max + '0' && getchar() == '\n')
        {
                return (enum options)(option - '0');
        }
        else
        {
                printf("Invalid option: ");
                printf("please enter a single digit between %d to %d\n", min, max);
                // Flush stdin
                while (getchar() != '\n');
        }
    }
}

void display_options_menu(void)
{
    printf("\n---Choose Option-------------------------\n");
    for (int i = 1; i < OPTIONS_COUNT; i++)
    {
        printf("%d. %s\n", i, options_str[i]);
    }
    // 0 is reserved for exit 
    printf("%d. %s\n", 0, options_str[0]);
    printf("-----------------------------------------\n");
}
