/*
 * CS 11, C Track, lab 7
 *
 * FILE: hash_table.c
 *
 *       Implementation of the hash table functionality.
 *
 */

/*
 * Include the declaration of the hash table data structures
 * and the function prototypes.
 */

/* SEE main.c FOR EXTRA CREDIT */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include "memcheck.h"


/*** Hash function. ***/

int hash(char *s)
{
    int i, len, count;

    count = 0;
    len = strlen(s);
    for (i = 0; i < len; i++) {
        count += (int) (s[i]);
    }
    count %= NSLOTS;
    return count;
}


/*** Linked list utilities. ***/

/* Create a single node. */
node *create_node(char *key, int value) {
    node *result = (node *)malloc(sizeof(node));

    if (result == NULL) {
        fprintf(stderr, "Fatal error: out of memory. "
                "Terminating program.\n");
        exit(1);
    }

    result->key = key;  /* Fill in the new node with the given value. */
    result->value = value;
    result->next = NULL;

    return result;
}



/* Free all the nodes of a linked list. */
void free_list(node *list) {
    node *n;     /* a single node of the list */

    while (list != NULL) {
        n = list;
        list = list->next;
        free(n->key);
        free(n);
    }
}


/*** Hash table utilities. ***/

/* Create a new hash table. */
hash_table *create_hash_table()
{
    int i;
    node **arr;
    hash_table *ht;

    ht = (hash_table *) malloc(sizeof(hash_table));
    arr = (node **) calloc(NSLOTS, sizeof(node *));
    if ((ht == NULL) || (arr == NULL)) {
        fprintf(stderr, "Fatal error: out of memory. "
                "Terminating program.\n");
        exit(1);
    }


    for (i = 0; i < NSLOTS; i++) {
        arr[i] = NULL;
    }
    ht->slot = arr;
    return ht;
}


/* Free a hash table. */
void free_hash_table(hash_table *ht)
{
    int i;

    for (i = 0; i < NSLOTS; i++) {
        free_list(ht->slot[i]);
    }
    free(ht->slot);
    free(ht);
}


/*
 * Look for a key in the hash table.  Return 0 if not found.
 * If it is found return the associated value.
 */
int get_value(hash_table *ht, char *key)
{
    int hash_val;
    node *link_list;

    hash_val = hash(key);
    link_list = ht->slot[hash_val];
    while (link_list != NULL) {
        if (!strcmp(link_list->key, key)) {
            return link_list->value;
        }
        link_list = link_list->next;
    }
    return 0;
}


/*
 * Set the value stored at a key.  If the key is not in the table,
 * create a new node and set the value to 'value'.  Note that this
 * function alters the hash table that was passed to it.
 */
void set_value(hash_table *ht, char *key, int value) {
    int hash_val;
    node *link_list;

    hash_val = hash(key);
    /* The 1st case handles if the key already exists in the hash table */
    if (get_value(ht, key)) {
        link_list = ht->slot[hash_val];
        while (link_list != NULL) {
            /* strcomp returns 0 if the string are the same */
            if (!strcmp(link_list->key, key)) {
                link_list->value = value;
                free(key);
                return;
            }
            link_list = link_list->next;
        }
    }
    /* The 2nd case creates a new node if the key doesn't exist in ht yet */
    else {
        link_list = create_node(key, value);
        link_list->next = ht->slot[hash_val];
        ht->slot[hash_val] = link_list;
    }
}


/* Print out the contents of the hash table as key/value pairs. */
void print_hash_table(hash_table *ht)
{
    int i;
    node *link_list;

    for (i = 0; i < NSLOTS; i++) {
        link_list = ht->slot[i];
        while (link_list != NULL) {
            printf("%s %d\n", link_list->key, link_list->value);
            link_list = link_list->next;
        }
    }
}