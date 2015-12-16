/*
 * heap.c
 *
 * Heap implementation.
 *
 * Luther Carroll
 * 391929
 * April 2015
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "heap.h"

/* Returns a pointer to a new, empty heap.
 */
Heap *createHeap(int map_size) {

    // Create a new heap.
	Heap * newHeap = (Heap *) malloc(sizeof(Heap));
    assert(newHeap);

	// Create the array of HeapItems.
	HeapItem * G;
	G = (HeapItem *) malloc(HEAP_SIZE * sizeof(HeapItem));
    assert(G);

    // Create the map array.
    int * m;
    m = (int *) malloc(map_size * sizeof(int));
    assert(m);

    newHeap->H = G;
    newHeap->map = m;
    newHeap->n = 0;     // is empty.
    newHeap->size = HEAP_SIZE;

	return newHeap;
}

/* Comparison function
 * 
 * Returns 1 if x > y.
 * Returns 0 if x <= y.
 */
int cmp(key_type x, key_type y) {
    
    return x > y ? 1 : 0;
}

/* Swap items
 */
void swapItems(Heap *h, int i, int j) {

    // Adjust the map.
    h->map[h->H[i].dataIndex] = j;
    h->map[h->H[j].dataIndex] = i;

    // Swap the heap items.
    HeapItem temp = h->H[i];
    h->H[i] = h->H[j];
    h->H[j] = temp;
}

/* Sift up. 
 */
void siftUp(Heap *h, int i) {

    /* Keep swapping the item with it's parent until the parent has lower key.
     * i in logic terminates loop at root i.e. when PARENT(i) = 0.
     */
    while (i && !cmp(h->H[i].key, h->H[PARENT(i)].key)) {
        swapItems(h, i, PARENT(i));
        i = PARENT(i);
    }
}

/* Sift down.
 */
void siftDown(Heap *h, int i) {

    int smallest;

    do {
        /* If there is a left child and it's key is smaller than i's key, 
         * then its the smallest.
         * If not, set the smallest to i,
         * then only need to compare i to right child.
         */
        smallest = LCHILD(i) < h->n && !cmp(h->H[LCHILD(i)].key, h->H[i].key)
            ? LCHILD(i) 
            : i;
        /* If there is a right child and it's key is smaller than
         * the current smallest's, then its the smallest.
         */
        if (RCHILD(i) < h->n 
            && !cmp(h->H[RCHILD(i)].key, h->H[smallest].key)) {
                    smallest = RCHILD(i);
        }
        // If the smallest is not the parent, swap it with the smallest.
        if (smallest != i) {
            swapItems(h, smallest, i);

            // Also, set i to smallest, to continue sifting next iteration.
            i = smallest;
        }
    } while (smallest != i);
}

/* Inserts dataIndex into h.
 *
 * Returns HEAP_SUCCESS if it has inserted, or HEAP_FAIL otherwise.
 */
int insert(Heap *h, int dataIndex, key_type key){

    // Check the size of the heap, if full, double the size.
    if (h->n > h->size) {
        h->size += HEAP_SIZE;
        printf("new size: %d\n", h->size);
        HeapItem * newH = (HeapItem *) realloc(h->H, h->size * sizeof(HeapItem));
        if (!newH) {
            printf("Error, ran out of memory in heap realloc\n");
            return HEAP_FAIL;
        } else {
            h->H = newH;
        }
    }

    // Make a new heap item.
    HeapItem newItem;
    newItem.dataIndex = dataIndex;
    newItem.key = key;

    // Insert heap item into next slot.
    int i = h->n;
    h->n++;
    h->H[i] = newItem;
    h->map[dataIndex] = i;

    // Sift the new item up the heap.
    siftUp(h, i);

    return HEAP_SUCCESS;
}

/* Returns the data index of the root.	
 */
int peek(Heap *h) {

    return h->H[0].dataIndex;
}
	
/* Returns the key of the root.
 */
key_type peekKey(Heap *h){
    
    return h->H[0].key;
}
  
/* Removes the root, returns the data index to it, 
 * and re-heapifies (possibly changing other items map values).
 */
int removeMin(Heap *h){

    // Get the data index to return before removing the item.
    int dataIndex = h->H[0].dataIndex;

    // Swap the first and last items. Also deincrement the next free slot.
    swapItems(h, 0, --(h->n));

    // Bound n.
    if (h->n < 0) {
        h->n = 0;
    }

    // Sift the new root down the heap.
    siftDown(h, 0);

    return dataIndex;
}

/* Changes the key of dataIndex and then re-heapifies.
 *
 * Returns HEAP_SUCCESS if it has inserted, or HEAP_FAIL otherwise.
 * Bug if dataIndex is out of range.
 */
int changeKey(Heap *h, int dataIndex, key_type newKey){

    // Make the index of the desired item explicit for readable code.
    int i = h->map[dataIndex];

    h->H[i].key = newKey;

    /* Re-heapify - If the item's new key is less than its parent, sift up,
     * else sift down. Preserves heap structure.
     */
    !cmp(h->H[i].key, h->H[PARENT(i)].key) ? siftUp(h, i) : siftDown(h, i);

    return HEAP_SUCCESS;
}

/* Free any memory you might of alloced in heap h.
 */
void destroyHeap(Heap *h){

    free(h->H);
    free(h->map);
    free(h);
}

/* Check if heap is empty.
 */
int isEmpty(Heap *h) {

    return(h->n == 0);
}

/* Remove item from heap.
 */
void removeItem(Heap *h, int dataIndex) {
    
    // Find the index of the item to remove.
    int i = h->map[dataIndex];

    // Swap the item to delete and the last item. Also deincrement the next free slot.
    swapItems(h, i, --(h->n));

    // Bound n.
    if (h->n < 0) {
        h->n = 0;
    }

    /* Re-heapify - If the item's new key is less than its parent, sift up,
     * else sift down. Preserves heap structure.
     */
    !cmp(h->H[i].key, h->H[PARENT(i)].key) 
        ? siftUp(h, i)
        : siftDown(h, i);
}

/* Print the contents of a heap.
 */
void printHeap(Heap *h) {

    printf("              PRINT HEAP:\n");
    printf("            heap size: %d\n", h->n);
    printf("----------------------------------------\n");
    for (int i = 0; i < h->n; i++) {
        printf("Slot %-3d: | dataIndex: %-3d, key: %-4.4e\n", i, h->H[i].dataIndex, h->H[i].key);
    }
    printf("----------------------------------------\n");
}
