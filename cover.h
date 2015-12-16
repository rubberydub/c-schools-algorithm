/*
 * cover.h
 *
 * Implementation of set cover algorithm.
 *
 * Luther Carroll
 * 391929
 * April 2015
 *
 */

#include "set.h"

#define COVER_COMPLETE 1
#define COVER_INCOMPLETE 0
#define COVERED 1
#define NOT_COVERED 0

/* CoverMap
 */
typedef struct coverMap {
    int covered;               // The amount of nodes covered.
    int required;           // The amount of nodes required to be covered.
    int *M; 	            // M[i] is COVERED if dataIndex i covered.
} CoverMap;

/* Makes a cover map of size n
 */
CoverMap *createCoverMap(int n);

/* Adds a set to the cover map.
 */
void addSetToCover(CoverMap *c, Set *s);

/* Check if the cover is complete.
 *
 * Returns COVER_COMPLETE or COVER_INCOMPLETE.
 */
int checkCover(CoverMap *c);
