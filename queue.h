/// file:
/// description:
/// author: mathew owusu

///
typedef struct queue_s * Queue;

///
Queue make_queue();

///
void destory(Queue q);

///
void enqueue(Queue q, void* item);

///
void dequeue(Queue q);

///
void* qfront(Queue q);

///
void* qrear(Queue q);

///
int is_empty(Queue q);

///
int is_full(Queue q);

///
int qlength(Queue q);
