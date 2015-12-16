/*
 * set.c
 *
 * Disjoint sets implementation.
 *
 * Luther Carroll
 * 391929
 * April 2015
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "set.h"

/* Makes a new set.
 */
Set *createSet(int dataIndex) {
    
    // Calloc a new set.
    Set * newSet = (Set *) calloc(1, sizeof(Set));
    assert(newSet);

    newSet->id = dataIndex;

    return newSet;
}

/* Appends an item to a set
 */
void append(Set *s, int dataIndex) {

    // Malloc a new node for the set.
    SetNode * newNode = (SetNode *) malloc(sizeof(SetNode));
    assert(newNode);

    // Fill in initial details.
    newNode->dataIndex = dataIndex;
    newNode->next = NULL;
    s->size++;

    // If the set is not empty, append newNode.
    if (s->head) {
        newNode->head = s->head;
        s->last->next = newNode;

    // If s is empty, newNode becomes the head.
    } else {
        newNode->head = NULL;
        s->head = newNode;
    }
    
    // Adjust the last pointer to the newNode.
    s->last = newNode;
}



/* Frees the space allocated for a set.
 */
void destroySet(Set *s) {

    // Free the nodes.
    SetNode * n = s->head;
    SetNode * temp;
    while (n) {
        temp = n;
        n = n->next;
        free(temp);
    }

    // Free the set.
    free(s);
}

/* Print the contents of a set.
 */
void printSet(Set *s) {

    SetNode * n = s->head;
    int i = 0;
    printf("printSet. Size of set: %d Set id: %d\n", s->size, s->id);
    while (n) {
        printf("Slot %d:    %d\n", i, n->dataIndex);
        n = n->next;
        i++;
    }
}
