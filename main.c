/*
 * main.c
 *
 * Luther Carroll
 * 391929
 * April 2015
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"
#include "heap.h"
#include "cover.h"

// Maximum length of characters in string. Arbitarty bound.
#define MAX_NUMBER_STRING_LEN 300

#define COST_RADIUS 100

// For stdlib qsort.
int compare(const void * x, const void * y) {
    
    return (*(Set **) y)->size - (*(Set **) x)->size;
}

int main(int argc, char *argv[]) {

    int num_houses;
    int num_schools;
    int total;

    char buff[MAX_NUMBER_STRING_LEN];
    
    // Fist two lines.
    for (int i = 0; i < 2; i++) {
        if (fgets(buff, MAX_NUMBER_STRING_LEN, stdin) != NULL) {
            // If !i i.e. first line.
            !i ? sscanf(buff, "%d", &num_houses)
               :sscanf(buff, "%d", &num_schools);
        }
    }

    total = num_houses + num_schools;

    // Now the graph can be initialised.
    Graph * g = createGraph(total);

    // Lines with edge information.
    while (fgets(buff, MAX_NUMBER_STRING_LEN, stdin) != NULL) {
        int tempV1, tempV2;
        float tempCost;

        sscanf(buff, "%d %d %f", &tempV1, &tempV2, &tempCost);

        // Input validation - edge values within range.
        if (tempV1 > total || tempV2 > total) {
            fprintf(stderr, 
                "Error: edge value out of range - greater than %d\n", 
                total);
            return(-1);
        }

        createEdge(g, tempV1, tempV2, tempCost);
    }

    // Input validation - check if graph is connected.
    if (!checkConnected(g)) {
        fprintf(stderr, "error: graph is not connected.\n");
        return(-1);
    }
    
    // Create an array of sets - one for each school.
    Set ** S = (Set **) malloc(sizeof(Set *) * num_schools);

    // Iterate over the schools, calling Dijkstra's to build the sets.
    for (int i = 0; i < num_schools; i++) {
        S[i] = dijkstra(g, num_houses + i, num_houses, total, COST_RADIUS);
    }

    // Sort the sets into decreasing order.
    qsort(S, num_schools, sizeof(Set *), compare);
    
    //Create a cover map for solving the cover; 
    CoverMap * M = createCoverMap(num_houses);

    // Solve the set cover.
    int i = 0; 
    while(!checkCover(M) && i < num_schools) {
        addSetToCover(M, S[i]);
        destroySet(S[i]);
        i++;
    }

    int j;
    // Print the school ids to stdout.
    for (j = 0; j < i; j++) {
        printf("%d\n", S[j]->id - num_houses);
    }

    return 0;
}
