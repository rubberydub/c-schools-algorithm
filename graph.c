/*
 * graph.c
 *
 * Graph implementation.
 *
 * Luther Carroll
 * 391929
 * April 2015
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"

/* Create a graph of size n without edges. Returns a pointer to a new graph.
 */
Graph *createGraph(int n) {

    // Allocate a new graph.
    Graph * newGraph = (Graph *) malloc(sizeof(Graph));
    assert(newGraph);

    /* Allocate the array of verticies. 
     * calloc to set memory to 0 as null pointers assumed later.
     */
    GraphVertex * W = (GraphVertex *) calloc(n, sizeof(GraphVertex));
    assert(W);

    newGraph->V = W;
    newGraph->size = n;

    return newGraph;
}

/* Create an edge.
 *
 * Assumes that the same edge is never added twice!
 */
void createEdge(Graph *g, int id1, int id2, cost_type c) {

    GraphVertex * v1 = g->V + id1;
    GraphVertex * v2 = g->V + id2;

    // Allocate two new edges.
    GraphEdge * newEdge1 = (GraphEdge *) malloc(sizeof(GraphEdge));
    assert(newEdge1);
    GraphEdge * newEdge2 = (GraphEdge *) malloc(sizeof(GraphEdge));
    assert(newEdge2);

    // Assign costs.
    newEdge1->cost = c;
    newEdge2->cost = c;

    // Initialise next pointers to NULL.
    newEdge1->next = NULL;
    newEdge2->next = NULL;

    // newEdge1 will point from v1 to v2 and vice versa.
    newEdge1->connection = v2;
    newEdge2->connection = v1;
    /* If the vertex has edges, append the new edge to the edge list.
     * Else, link the vertex to the edge, as it's the first edge.
     */
    v1->edges ? 
        v1->last->next = newEdge1 
        : v1->edges = newEdge1;
    v2->edges ?
        v2->last->next = newEdge2 
        : v2->edges = newEdge2;

    // Update the pointer to the last edge.
    v1->last = newEdge1;
    v2->last = newEdge2;
}

/* Returns the ID of the vertex an edge is connected to.
 */
int connectedTo(GraphEdge *e, Graph *g) {

    return IDENTIFY(e->connection, g->V);
}

/* Explores a vertex.
 *
 * For DFS and derivatives.
 */
void explore(Graph *g, int visited[], GraphVertex *v) {
    
    visited[IDENTIFY(v, g->V)] = VISITED_TRUE;
   
    // Iterate over all the edges of a vertex.
    GraphEdge * edge = v->edges;
    while (edge) {
        // Explore the connected vertex if not already visited, 
        if (!visited[IDENTIFY(edge->connection, g->V)]) {
            explore(g, visited, edge->connection);
        }
        // Go to next edge. Terminates loop when e->next = NULL.
        edge = edge->next;
    }
}

/* Checks if graph is connected. Returns CONNECTED_TRUE or CONNECTED_FALSE.
 *
 * Essentially just performs DFS from only the initial vertex.
 * Assumes v->visited is false for all v in g.
 */
int checkConnected(Graph *g) {

    int visited[g->size] = {VISITED_FALSE};

    // Explore from initial vertex.
    explore(g, visited, g->V); 

    // If an edge is unvisited then graph is disconnected. Takes O(n).
    for (int i = 0; i < g->size; i++) {
        if (!visited[i]) {
            return CONNECTED_FALSE;
        }
    }

    return CONNECTED_TRUE;
}

/* Destroy graph.
 */
void destroyGraph(Graph *g) {

    GraphEdge * edge;

    // Free all edges.
    for (int i = 0; i <= g->size; i++) {
        edge = g->V[i].edges;
        while (edge) {
            GraphEdge * temp = edge;
            edge = edge->next;
            free(temp);
        }
    }

    // Free the graph.
    free(g->V);
    free(g);
}
