/*
 * dijkstra.h
 *
 * Implementation of Dijkstra's algorithm.
 *
 * Luther Carroll
 * 391929
 * April 2015
 *
 */

#include "graph.h"
#include "set.h"

// For the limits of vertex costs.
#include <float.h>
//#include <limits.h>

/* The limit (i.e. infinity) of the primitive type of the edge costs.
 * Float for the purposes of this program.
 * Can be changed to int for reusability.
 */
#define COST_LIMIT FLT_MAX
//#define COST_LIMIT INT_MAX;

#define NO_PREVIOUS -1

/* The primitive type of the edge costs.
 * Float for the purposes of this program.
 * Can be changed to int for reusability.
 */
typedef float cost_type;
//typedef int cost_type;

/* Dijksta's algorithm.
 *
 * Takes a graph, the id of the source, and a cost radius limit. 
 * Returns an array - previous[vertex id] = id of previous vertex. 
 */
Set *dijkstra(Graph *g, int id, int num_houses, int total, cost_type cost_radius);
