#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../include/polynomial_operations.h"
#include "../include/utils.h"

void free_polynomial(struct poly_node *polynomial)
{
    struct poly_node *curr = polynomial;
    while (curr != NULL)
    {
        struct poly_node *next = curr->next;
        free(curr);
        curr = next;
    }
}

void print_polynomial(const struct poly_node *polynomial)
{
    printf("\nCurrent polynomial f(x): ");

    if (polynomial == NULL)
    {
        printf("NONE\n");
    }
    else
    {
        const struct poly_node *curr = polynomial;
        for (curr; curr != NULL; curr = curr->next)
        {
            // Blank
            printf(curr == polynomial ? "" : " ");

            // Signs
            printf(curr->coeff < 0 ? "-" : "");
            printf(curr->coeff > 0 && curr != polynomial ? "+" : "");
            printf(curr == polynomial ? "" : " ");

            // Coefficient
            int abs_coeff = abs(curr->coeff);
            printf(curr->exp == 0 ? "%d" : "", abs_coeff);
            // 1 is not printed for non constant terms
            printf(curr->exp != 0 && abs_coeff != 1 ? "%d" : "", abs_coeff);

            // Variable
            printf(curr->exp == 1 ? "x" : "");
            printf(curr->exp > 1 ? "x^%d" : "", curr->exp);
            printf(curr->exp < 0 ? "x^%d" : "", curr->exp);
        }
        printf("\n");
    }
}

struct poly_node *insert_node(struct poly_node *polynomial, int coeff, int exp)
{
    // Skip if coefficient is 0
    if (coeff == 0)
    {
        return polynomial;
    }

    // Create new node
    struct poly_node *new_node;
    new_node = malloc(sizeof(struct poly_node));
    if (new_node == NULL)
    {
        printf("Could not insert node: ");
        printf("Memory allocation failed\n");
        return polynomial;
    }
    new_node->coeff = coeff;
    new_node->exp = exp;

    // Insert

    if (polynomial == NULL)
    {
        new_node->next = NULL;
        polynomial = new_node;
        return polynomial;
    }

    struct poly_node *curr = polynomial;
    struct poly_node *prev = NULL;
    for (curr, prev; curr != NULL; prev = curr, curr = curr->next)
    {
        // Add to existing node if exponent is same
        if (curr->exp == exp)
        {
            curr->coeff += coeff;
            // Delete node if coefficient is 0
            if (curr->coeff == 0)
            {
                // Delete head
                if (prev == NULL)
                {
                    polynomial = curr->next;
                }
                // Delete non-head
                else
                {
                    prev->next = curr->next;
                }
                free(curr);
            }
            free(new_node);
            return polynomial;
        }
        else if (curr->exp < exp)
        {
            // Insert at head
            if (prev == NULL)
            {
                new_node->next = polynomial;
                polynomial = new_node;
            }
            // Insert at non-head
            else
            {
                new_node->next = curr;
                prev->next = new_node;
            }
            return polynomial;
        }
    }
    // If not inserted yet, insert at tail
    new_node->next = NULL;
    prev->next = new_node;
    return polynomial;
}

struct poly_node *delete_node(struct poly_node *polynomial, int exp)
{
    if (polynomial == NULL)
    {
        printf("Polynomial f(x) doesn't exists\n");
        return polynomial;
    }
    struct poly_node *curr = polynomial;
    struct poly_node *prev = NULL;

    for (curr, prev; curr != NULL; prev = curr, curr = curr->next)
    {
        if (curr->exp == exp)
        {
            // Delete head
            if (prev == NULL)
            {
                polynomial = curr->next;
            }
            // Delete non-head
            else
            {
                prev->next = curr->next;
            }
            free(curr);
            return polynomial;
        }
    }
    // If not found
    printf("Term with exponent %d not found\n", exp);
    return polynomial;
}

struct poly_node *add_monomial(struct poly_node *polynomial)
{
    int coeff, exp;
    do
    {
        printf("\nexponent: ");

    } while (!get_int_input(&exp, ALLOW_ALL));

    do
    {
        printf("coefficient of x^%d: ", exp);

    } while (!get_int_input(&coeff, ALLOW_ALL));

    // Insert
    polynomial = insert_node(polynomial, coeff, exp);
}

struct poly_node *input_polynomial(struct poly_node *polynomial)
{
    // Free existing one
    if (polynomial != NULL)
    {
        free_polynomial(polynomial);
        polynomial = NULL;
    }

    // Get number of terms in polynomial
    int terms;
    do
    {
        printf("\nType Number of terms in polynomial: ");

    } while (!get_int_input(&terms, POSITIVE_ONLY));

    // Ask user again if terms are too many to input manually
    // TODO: give proper exit option to user in loop below 
    if (terms > 15)
    {
        printf("That's pretty large number of terms for this simple program\n");
        printf("You might have a hard time inputting all of them manually\n");
        printf("Do you want to continue? (y/n): ");
        char option = getchar();
        // Flush stdin
        while (getchar() != '\n');
        switch (option)
        {
        case 'y':
            // Intentional fallthrough
        case 'Y':
            break;
        case 'n':
            // Intentional fallthrough
        case 'N':
            return polynomial;
        default:
            printf("I'll consider it as a no\n");
            return polynomial;
        }
    }

    // Insert
    for (int i = 0; i < terms; i++)
    {
        printf("\n-Term %d-------------------", i + 1);
        polynomial = add_monomial(polynomial);
        printf("--------------------------\n");
        print_polynomial(polynomial);
        
    }
    return polynomial;
}

struct poly_node *delete_monomial(struct poly_node *polynomial)
{
    // Check if polynomial exists
    if (polynomial == NULL)
    {
        printf("Polynomial f(x) doesn't exists\n");
        return polynomial;
    }

    // Get exponent
    int exp;
    do
    {
        printf("\nType the exponent of the term to delete: ");

    } while (!get_int_input(&exp, ALLOW_ALL));

    // Delete
    polynomial = delete_node(polynomial, exp);
    return polynomial;
}

struct poly_node *differentiate_polynomial(struct poly_node *polynomial)
{
    if (polynomial == NULL)
    {
        return polynomial;
    }

    struct poly_node *curr = polynomial;
    struct poly_node *prev = NULL;
    while (curr != NULL)
    {
        // Delete constant
        if (curr->exp == 0)
        {
            // Delete head
            if (prev == NULL)
            {
                polynomial = curr->next;
            }
            // Delete non-head
            else
            {
                prev->next = curr->next;
            }
            struct poly_node *temp = curr;
            curr = curr->next;
            free(temp);
        }
        // Differentiate non-constant terms
        else
        {
            // Check for overflow
            if (abs(curr->exp) > INT_MAX / abs(curr->coeff))
            {
                printf("Could not differentiate polynomial: ");
                printf("Integer overflow\n");
                return NULL;
            }
            else
            {
                curr->coeff *= curr->exp;
                curr->exp--;

                prev = curr;
                curr = curr->next;
            }
        }
    }
    return polynomial;
}

void substitute_polynomial(const struct poly_node *polynomial)
{
    // Check if polynomial exists
    if (polynomial == NULL)
    {
        printf("Polynomial f(x) doesn't exists\n");
    }
    else
    {
        // Get x
        int x;
        do
        {
            printf("\nType the value of x to substitute: ");

        } while (!get_int_input(&x, ALLOW_ALL));

        long result = 0;
        const struct poly_node *curr = polynomial;
        for (curr; curr != NULL; curr = curr->next)
        {
            long pow_res = pow_int(x, curr->exp);
            if (pow_res == 0)
            {
                // If 0, checking for overflow is unnecessary
                // Plus, it will yield division by 0 error
                // result += cur->coeff * 0, thus skip 
                continue;
            }

            // Check for multiplication overflow
            if (abs(curr->coeff) > LONG_MAX / abs(pow_res))
            {
                printf("Could not substitute polynomial: ");
                printf("Integer overflow\n");
                return;
            }

            long prev_result = result;
            long term_mult = curr->coeff * pow_res;
            result += term_mult;

            // Check for addition overflow by checking with inverse operation
            if (result - prev_result != term_mult)
            {
                printf("Could not substitute polynomial: ");
                printf("Integer overflow\n");
                return;
            }
        }
        printf("\nf(%d) = %ld\n", x, result);
    }
}