#ifndef POLYNOMIAL_OPERATIONS_H
#define POLYNOMIAL_OPERATIONS_H

/**
 * --------------------------------------------
 * NOTE:
 * All polynomial linked lists are assumed to be well-ordered
 * that is, exponents are in descending order
 * Functions that modify polynomial should maintain this property
 * and functions that use polynomial might assume this property
 * --------------------------------------------
*/


// Node representing a term in a polynomial linked list
struct poly_node
{
    int coeff;  
    int exp;
    struct poly_node *next; 
};

// Function prototypes

// Frees a memory allocated to polynomial linked list
void free_polynomial(struct poly_node *polynomial);

// Prints a polynomial linked List with a format:
// f(x): -2x^3 + 5x^2 + 3x - 1
// If polynomial is NULL, prints NONE
void print_polynomial(const struct poly_node *polynomial);

// Make and insert a node into polynomial in descending order of exponent
// If there exits a node with same exponent, adds it to a existing node
// Deletes a node if coefficient becomes 0 after addition
struct poly_node *insert_node(struct poly_node *polynomial, int coeff, int exp);

// Delete a node with given exponent from polynomial if it exists
struct poly_node *delete_node(struct poly_node *polynomial, int exp);

// Append a monomial to current polynomial
// Gets coefficient and exponent of monomial from user using get_int_input()
struct poly_node *add_monomial(struct poly_node *polynomial);

// Input polynomial from user
// Frees existing polynomial if any
// Gets number of terms in polynomial from user and appends that many
// TODO: Give user a option to exit loop
struct poly_node *input_polynomial(struct poly_node *polynomial);

// Delete a monomial from polynomial
struct poly_node *delete_monomial(struct poly_node *polynomial);

// Differentiate given polynomial
// Nodes 0x^0 are deleted after differentiation
// Does not differentiate if coeff overflows int and returns NULL regardless
struct poly_node *differentiate_polynomial(struct poly_node *polynomial);

// Calculate and print f(x) for a given x and polynomial f
// f(x) long type to prevent overflow
void substitute_polynomial(const struct poly_node *polynomial);

#endif // POLYNOMIAL_OPERATIONS_H