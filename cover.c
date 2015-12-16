/*
 * cover.c
 *
 * Implementation of set cover algorithm.
 *
 * Luther Carroll
 * 391929
 * April 2015
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "cover.h"

/* Makes a cover map of size n
 */
CoverMap *createCoverMap(int n) {

    // Malloc a new cover map.
    CoverMap * newCoverMap = (CoverMap *) malloc(sizeof(CoverMap));
    assert(newCoverMap);

    /* Calloc the map array.
     * Calloced as NOT_COVERED = 0;
     */
    int * newMap = (int *) calloc(n, sizeof(int));
    assert(newMap);

    // Fill in initial details.
    newCoverMap->covered = 0;   // Nothing covered.
    newCoverMap->required = n;
    newCoverMap->M = newMap;

    return newCoverMap;
}

/* Adds a set to the cover map.
 */
void addSetToCover(CoverMap *c, Set *s) {

    /* Iterate through the set and mark all it's nodes
     * as covered in the cover map.
     */
    SetNode * n = s->head;
    while (n) {
        if (!c->M[n->dataIndex]) {
            c->M[n->dataIndex] = COVERED;
            c->covered++;
        }

        n = n->next;
    }
}

/* Check if the cover is complete.
*
* Returns COVER_COMPLETE or COVER_INCOMPLETE.
*/
int checkCover(CoverMap *c) {

    return c->covered == c->required ? COVER_COMPLETE : COVER_INCOMPLETE;
}
