#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "memcheck.h"

/* Function prototypes */
void build_list(int len, int *arr);
void update_list(int len, int *arr, int *arr2);
void set_list(int len, int *arr, int *arr2);
void print_list(int len, int *arr);

int main(int argc, char * argv[]) {
    /* Variable declarations */
    int cell_len, num_gens, i;
    int *cells;
    int *temp_cells; /* updated array which later gets copied into cells */

    /* Checks for appropriate number of arguments */
    if (argc != 3) {
        fprintf(stderr, "usage: %s n\n", argv[0]);
        exit(1);
    }

    /* Variable assignments */
    cell_len = atoi(argv[1]);
    num_gens = atoi(argv[2]);

    /* Dynamic allocations */
    cells = (int *) calloc(cell_len, sizeof(int));
    temp_cells = (int *) calloc(cell_len, sizeof(int));

    /* Check that the calloc calls succeeded. */
    if  ((cells == NULL) || (temp_cells == NULL)) {
        fprintf(stderr, "Error! Memory allocation failed!\n");
        exit(1);  /* abort the program */
    }
    print_memory_leaks();

    /* Assign random values of 0 or 1 to array of length cell_len */
    if (cell_len > 2) {
        build_list(cell_len, cells);
    }

    /* Updates and prints the array according to num_gens */
    if (num_gens != 0) {
        print_list(cell_len, cells);
    }
    if (num_gens > 1) {
        for (i = 1; i < num_gens; i++) {
            update_list(cell_len, cells, temp_cells);
            set_list(cell_len, cells, temp_cells);
            print_list(cell_len, cells);
        }
    }

    free(cells);
    return 0;
}

/* 
 * build_list:
 *    This function fills a previously dynamically allocated array with 
 *    approximately half ones and half zeros, by using the rand() function.
 *
 *    Arguments
 *        - len: the length of the dynamically allocated array that has our
 *               cellular automaton.
 *        - *arr: a pointer that represents our cellular automaton.
 *
 *    Returns:
 *        - Void function merely modifies input array in heap, does not
 *          return a value.
 */
void build_list(int len, int *arr) {
    int i;
    time_t t;
    srand((unsigned) time(&t));

    for (i = 1; i < (len -1); i++) {
        arr[i] = rand() % 2; /* about 50% of array has value 1 */
    }
}

/* 
 * update_list:
 *    This function creates an updated array that after numerous updates,
 *    creates a fractal pattern. The input array arr will be composed of 
 *    ones and zeros and will update according to the following rules: if
 *    the current cell is zero, and one of the two adjacent cells is one
 *    (but not both), we set the current cell to be one. Otherwise we set
 *    the current cell to be empty. This version uses array operations. 
 *
 *    Arguments
 *        - len: the length of the dynamically allocated array that has our
 *          cellular automaton.
 *        - *arr: a pointer that represents our cellular automaton.
 *        - *arr2: a pointer that represents our updated cellular automaton,
 *           whose values will later be set into *arr.
 *
 *    Returns:
 *        - Void function merely modifies input array in heap, does not
 *          return a value.
 */
void update_list(int len, int *arr, int *arr2) {
    int i;

    if (len > 2) {
        for (i = 1; i < len - 1; i++) {
            if ((arr[i] == 0) && ((arr[i - 1] == 1) != (arr[i + 1] == 1))) {
              arr2[i] = 1;
            }
            else {
               arr2[i] = 0;
            }
        }        
    }
}

/* 
 * set_list:
 *    This function simply copies the elements of one array into another.
 *
 *    Arguments
 *        - len: the length of the dynamically allocated array that has our
 *          cellular automaton.
 *        - *arr: a pointer that represents our cellular automaton.
 *        - *arr2: a pointer that represents our updated cellular automaton,
 *           whose values will later be set into *arr.
 *
 *    Returns:
 *        - Void function merely modifies input array in heap, does not
 *          return a value.
 */
void set_list(int len, int *arr, int *arr2) {
    int i;

    for (i = 1; i < len; i++) {
        arr[i] = arr2[i];
    }
}

/* 
 * print_list:
 *    This function prints a ". " for each zero and a "* " for each one in
 *    our input cellular automaton array. Note that it creates a new line
 *    after completely iterating through the array so that the function when
 *    called in a loop will create the desired fractal pattern.
 *
 *    Arguments
 *        - len: the length of the dynamically allocated array that has our
 *          cellular automaton.
 *        - *arr: a pointer that represents our cellular automaton.
 *
 *    Returns:
 *        - Void function merely modifies input array in heap, does not
 *          return a value.
 */
void print_list(int len, int *arr) {
    int i;

    for (i = 0; i < len; i++) {
        if (arr[i] == 0) {
            printf(". ");
        }
        else {
            printf("* ");
        }
    }
    printf("\n");
}