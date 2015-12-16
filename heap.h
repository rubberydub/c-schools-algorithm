/*
 * heap.h
 *
 * Heap implementation.
 *
 * Luther Carroll
 * 391929
 * April 2015
 *
 */

#define HEAP_SIZE 1024	    // initial size of heap.
#define HEAP_SUCCESS 0		// returned if insert() succeeds
#define HEAP_FAIL 1 		// returned if insert() fails

#define LCHILD(x) 2*x + 1
#define RCHILD(x) 2*x + 2
#define PARENT(x) x/2

/* The primitive type of the keys.
 * Float for the purposes of this program.
 * Can be changed to int for reusability.
 */
typedef float key_type;
//typedef int key_type;

/* HeapItem
 */
typedef struct item {
    key_type key; 		    // the key for deciding position in heap
    int dataIndex;          // the payload index provided by the calling program
} HeapItem;

/* Heap
 */
typedef struct heap {
    HeapItem *H; 		    // the underlying array
    int *map; 	            /* map[i] is index into H of location of payload
                             * with dataIndex i
                             */
    int n; 	                // the number of items currently in the heap
    int size; 	            // the maximum number of items allowed in the heap
} Heap;

/* That returns a pointer to a new, empty heap
 */
Heap *createHeap(int size);	

/* Inserts dataIndex into h. 
 *
 * Returns HEAP_SUCCESS if it has inserted, or HEAP_FAIL otherwise.
 */
int insert(Heap *h, int dataIndex, key_type key);

/* Returns the data index of the root.	
 */
int peek(Heap *h);	

/* Returns the key of the root.
 */
key_type peekKey(Heap *h);  

/* Removes the root, returns the data index to it, i
 * and re-heapifies (possibly changing other items map values).
 */
int removeMin(Heap *h); 

/* Changes the key of dataIndex and then re-heapifies.
 *
 * Returns HEAP_SUCCESS if it has inserted, or HEAP_FAIL otherwise.
 */
int changeKey(Heap *h, int dataIndex, key_type newKey);

/* Free any memory you might of alloced in heap c	
 */
void destroyHeap(Heap *h); 

/* Check if heap is empty.
 */
int isEmpty(Heap *h); 

/* Remove item from heap.
 */
void removeItem(Heap *h, int dataIndex);

/* Print the contents of a heap.
 */
void printHeap(Heap *h);
