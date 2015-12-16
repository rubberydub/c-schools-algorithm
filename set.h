/*
 * set.h
 *
 * Disjoint sets implementation.
 *
 * Luther Carroll
 * 391929
 * April 2015
 *
 */

#ifndef _SET_INCL_GUARD
#define _SET_INCL_GUARD

/* SetNode
 */
typedef struct node {
    struct node *next;      // Points to the next node.
    node *head;      // Points to the head of the set
    int dataIndex;          // The payload index provided by the calling program
} SetNode;

/* Set
 */
typedef struct set {
    SetNode *head;      // Points to the head of the set.
    SetNode *last;      // Points to the last node in the set
    int id;                 // The payload index of the id of the set.
    int size;               // The size of the set.
} Set;

/* Makes a new set.
 */
Set *createSet(int dataIndex);

/* Appends an item to a set
 */
void append(Set *s, int dataIndex);

/* Frees the space allocated for a set.
 */
void destroySet(Set *s);

/* Print the contents of a set.
 */
void printSet(Set *s);

#endif
