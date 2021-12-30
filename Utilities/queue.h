/// file: queue.h
/// description: A header file that contains the public functions for queue
/// author: mathew owusu


/// The struct that contains the queue. THe functions in this file create,
/// modify and access this struct
typedef struct queue_s * Queue;


/// Creates a new instance of the queue struct
/// @param int max_cap is the max amount of elements the queue can hold
/// @return a pointer to the created queue struct
Queue make_queue(int max_cap);


/// Frees the memory inside the queue struct, and frees the memeory allocated to
/// the queue struct
/// @param Queue q is a pointer to a queue struct
void destory_queue(Queue q);


/// Adds a generic element into the queue
/// @param Queue q is a pointer to a queue struct
/// @param void *item is an element that has no type
void enqueue(Queue q, void *item);


/// Remove the first item from the queue
/// @param Queue q is a pointer to a queue struct
/// @param void *item is an element that has no type
void dequeue(Queue q);


/// Returns the element at the front of the queue
/// @param Queue q is a pointer to a queue struct
// @return the first element in the queue
void *qfront(Queue q);


/// Returns the element at the end of the queue
/// @param Queue q is a pointer to a queue struct
// @return the last element in the queue
void *qrear(Queue q);


/// Returns the element at the specified position
/// @param Queue q is a pointer to a queue struct
/// @param int position is the index
/// @return the element in queue at the specified qposition
void *qposition(Queue q, int position);


/// Returns the list inside the queue struct
/// @param Queue q is a pointer to a queue struct
/// @return the list inside the queue struct
void **get_queue(Queue q);


/// Returns whether or no the list inside the queue struct is empty
/// @param Queue q is a pointer to a queue struct
/// @return 1 if true, 0 if false
int is_q_empty(Queue q);


/// Returns whether or no the list inside the queue struct is full
/// @param Queue q is a pointer to a queue struct
/// @return 1 if true, 0 if false
int is_q_full(Queue q);


/// Returns the length of the list inside the queue struct
/// @param Queue q is a pointer to a queue struct
int qlength(Queue q);
