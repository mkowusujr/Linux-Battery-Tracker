// file: queue
// description: a queue of length 5
// author: mathew owusu jr
#include <stdlib.h>
#include "queue.h"
#define LEN 5


//
typedef struct queue_s{
    int curr_capacity;
    void* list[LEN];
}* Queue;


//
//
//
Queue* make_queue()
{
    Queue *q = NULL;
    q = (Queue*)(malloc(sizeof(struct queue_s)));
    return q;
}


// 
//
// @param:
void enqueue(Queue *q)
{
    
}


//
//
// @param:
void dequeue(Queue *q)
{

}


//
//
// @param:
void* qfront(Queue *q)
{
    return 0;
}


//
//
// @param:
void* qrear(Queue *q)
{
    return 0;
}


//
//
// @param:
int is_empty(Queue *q)
{
    return 0;
}


// 
//
// @param:
int is_full(Queue *q)
{
    return 0;
}


//
//
// @param:
int qlength(Queue *q)
{
    return 0; 
}
