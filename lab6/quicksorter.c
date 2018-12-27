/*
 * quicksorter.c:
 *
 *     The function applies a quicksorter algorithm on integer arguments from
 *     the command line and defaults to print them (printing can be
 *     suppressed with any number of -q command line arguments). All integer
 *     arguments are processed into a linked list, created from a recursively
 *     defined structure, node (see linked_list.h). 
 *     
 *     The linked list pointer is sent to the quicksorter algorithm which 
 *     recursively sorts the list and returns a duplicate linked list
 *     pointer. It sorts in accordance with the same rules as the C quicksort
 *     algorithm, by creating lists of values less than a starting value, and
 *     greater than a starting value, using recursion to sort these
 *     sub-lists, and appending the list together.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "linked_list.h"
#include "memcheck.h"

/*
 * The quicksort function creates a duplicate linked list that is sorted
 * under the quicksort algorithm.
 */
node *quicksort(node *list);


int main(int argc, char *argv[]) {
    /*
     * The variable func takes the value of 0 if there is no suppression
     * of output. Otherwise it takes the value of 1 if at least one command
     * argument is -q.
     * 
     * The variable is_num_args is 0 if there are no numerical arguments,
     * in which case the function will return a usage error. Otherwise,
     * it takes a non-zero value and processes the quicksorter algorithm on
     * the integer arguments.
     */
    int i, func, is_num_args;
    node *output_list;
    node *input_list;

    is_num_args = 0;
    input_list = NULL;

    /* 
     * Checks if there are command-line arguments at all and 
     * returns a usage message if there are none
     */
    if (argc == 1) {
        fprintf(stderr, "usage: %s [-q] number1 [number2...]\n", argv[0]);
        exit(1);
    }

    /* 
     * Processes the command-line arguments and creates the linked list
     * representing the input values. Also sets func as described above.
     */
    func = 0;
    for (i = 1; i < argc; i++) {
        if ((strcmp(argv[i], "-q")) == 0) {
            func = 1;
        }
        else {
            is_num_args++;
            input_list = create_node(atoi(argv[i]), input_list);
        }
    }

    /* Checks if there are integer value arguments at all */
    if (!is_num_args) {
        fprintf(stderr, "usage: %s [-q] number1 [number2...]\n", argv[0]);
        exit(1);
    }

    /* 
     * Sorts the input list into a copied output_list (input_list does not
     * change). Then checks func to determine whether or not to suppress the
     * output.
     */
    output_list = quicksort(input_list);
    if (func == 0) {
        print_list(output_list);
    }

    /* Memory allocation freeing */
    free_list(input_list);
    free_list(output_list);
    print_memory_leaks();
    return 0;
}


/*
 * quicksort:
 *
 *     The quicksorter algorithm recursively sorts the list and returns a 
 *     duplicate linked list pointer. It sorts in accordance with the same 
 *     rules as the C quicksort algorithm, by creating lists of values less
 *     than a starting value, and greater than a starting value, using 
 *     recursion to sort these sub-lists, and appending the list together.
 *
 *     Input Arg: A pointer to a linked list of randomly ordered
 *                 numbers. 
 *
 *     Return Arg: A pointer to a duplicated newly sorted linked list
 *                 of equal length the input and comprising of the same
 *                 numbers.
 */
node *quicksort(node *list) {
    node *a_node;
    node *node_result; /* The node the function will return */
    node *node_left;   /* The nodes lesser or equal to the examined value */
    node *node_right;  /* The nodes greater than the examined value */
    node *temp_left;
    node *temp_right;

    node_result = copy_list(list);

    /* Base case of the recursion, if empty list or single node list */
    if (list == NULL) {
        return node_result;
    }
    else if (list->next == NULL) {
        return node_result;
    }

    /* Setting initial values for variables */
    free_list(node_result->next);
    node_result->next = NULL;
    node_left = NULL;
    node_right = NULL;
    /* 
     * Recursive case (two recursions): applies quicksort on those values 
     * less than or equal to the given value at a_node as well as on those
     * values greater than the given value. These values are stored in
     * node_left and node_right. Makes sure to free previously allocated
     * nodes.
     */
    for (a_node = list->next; a_node != NULL; a_node = a_node->next) {
        if (a_node->data <= node_result->data) {
            node_left = create_node(a_node->data, node_left);
        }
        else {
            node_right = create_node(a_node->data, node_right);
        }
    }

    free_list(a_node);

    temp_left = quicksort(node_left);
    free_list(node_left);
    node_left = temp_left;

    temp_right = quicksort(node_right);
    free_list(node_right);
    node_right = temp_right;

    /* Recombines sorted lists and frees previously allocated nodes */
    node_left = append_lists(node_left, node_result);
    free_list(node_result);
    free_list(temp_left);

    node_result = append_lists(node_left, node_right);
    free_list(node_left);
    free_list(node_right);

    /* Performs check on node_result to ensure it is indeed sorted. */
    assert(is_sorted(node_result) == 1);
    return node_result;
}