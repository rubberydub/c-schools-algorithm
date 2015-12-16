/*
 * graph.h
 *
 * Graph implementation.
 *
 * Luther Carroll
 * 391929
 * April 2015
 *
 */

#ifndef _GRAPH_INCL_GUARD
#define _GRAPH_INCL_GUARD

#define VISITED_TRUE 1
#define VISITED_FALSE 0
#define CONNECTED_TRUE 1 
#define CONNECTED_FALSE 0

/* For finding the array index of a vertex by address.
 */
#define IDENTIFY(ELEMENT, ARRAY) ELEMENT - ARRAY

/* The primitive type of the edge costs.
 * Float for the purposes of this program.
 * Can be changed to int for reusability.
 */
typedef float cost_type;
//typedef int cost_type;

/* Graph vertex.
 */
typedef struct vertex {
    struct edge *edges;         // The edges connected to this vertex.
    struct edge *last;          // The last edge in the edge list.
} GraphVertex;

/* Graph Edge.
 */
typedef struct edge {
    GraphVertex *connection;    // The vertex the edge connects to.
    struct edge *next;          // The next edge - from the connected vertex.
    cost_type cost;             // The travel distance.
} GraphEdge;

/* Graph.
 */
typedef struct graph {
    GraphVertex *V;             // Points to the array of verticies.
    int size;                   // The amount of verticies.
} Graph;


/* Create a graph of size n. Returns a pointer to a new graph.
 */
Graph *createGraph(int n);

/* Create an edge.
 *
 * Assumes that the same edge is never added twice!
 */
void createEdge(Graph *g, int v1, int v2, cost_type cost);

/* Checks if graph is connected. Returns CONNECTED_TRUE or CONNECTED_FALSE.
 *
 * Essentially just performs DFS from only the initial vertex.
 * Assumes v->visited is false for all v in g.
 */
int checkConnected(Graph *g);

/* Returns the ID of the vertex an edge is connected to.
 */
int connectedTo(GraphEdge *e, Graph *g);

/* Destroy graph.
 */
void destroyGraph(Graph *g);

#endif
