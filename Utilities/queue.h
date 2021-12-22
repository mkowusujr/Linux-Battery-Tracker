/// file:
/// description:
/// author: mathew owusu

///
typedef struct queue_s * Queue;

///
Queue make_queue(int max_cap);

///
void destory_queue(Queue q);

///
void enqueue(Queue q, void* item);

///
void dequeue(Queue q);

///
void* qfront(Queue q);

///
void* qrear(Queue q);

///
void* qposition(Queue q, int position);

///
void** get_queue(Queue q);

///
int is_q_empty(Queue q);

///
int is_q_full(Queue q);

///
int qlength(Queue q);
