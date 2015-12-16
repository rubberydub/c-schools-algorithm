/*
 * dijkstra.c
 *
 * Implementation of Dijkstra's algorithm.
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

/* Dijkstra's algorithm.
 *
 * Takes a graph, the id of the source, and a cost radius limit. 
 * Returns an array - previous[vertex id] = id of previous vertex. 
 */
Set *dijkstra(Graph *g, int id, int num_houses, int total, cost_type cost_radius) {

    cost_type distance[g->size];
    int previous[g->size];
    Heap * h = createHeap(total);
    Set * s = createSet(id);

    for (int i = 0; i < g->size; i++) {
        distance[i] = COST_LIMIT;
        previous[i] = NO_PREVIOUS;
    }

    int u;          // Current vertex.
    int v;          // Vertex connected to u by an edge.
    cost_type d;    // Distance to u + edge cost.
    
    // Insert the root into the heap.
    insert(h, id, 0);
    distance[id] = 0;

    // Iterate until the queue is empty.
    while (!isEmpty(h)) {
        u = removeMin(h);

        // u must now be in s. append to s if not a school vertex.
        if (u < num_houses) {
            append(s, u);
        }

        // Iterate over all edges.
        GraphEdge * edge = g->V[u].edges;
        while (edge) {
            v = connectedTo(edge, g);
            d = distance[u] + ((cost_type) edge->cost);

            // If distance within radius and distance is a shorter path to v.
            if (d <= cost_radius && d < distance[v]) {    

                /* If distance to v is COST_LIMIT, then this is the first time
                 * the algorithm has encountered v, so add it to the heap.
                 * If not, then it must be on the heap, so change its key.
                 */
                distance[v] == COST_LIMIT 
                    ? insert(h, v, d)
                    : changeKey(h, v, d);

                // Update the arrays.
                distance[v] = d;
                previous[v] = u;
            }
            edge = edge->next;
        }
    }
    destroyHeap(h);

    return s;
}
