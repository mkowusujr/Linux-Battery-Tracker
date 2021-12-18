// file: queue
// description: a queue of length 5
// author: mathew owusu jr
#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#define LEN 5


//
typedef struct queue_s{
    int curr_capacity;
    int max_capacity;
    void** list;
}* Queue;


//
//
//
Queue make_queue(int max_cap)
{
    Queue q = malloc(sizeof(struct queue_s));
    q->curr_capacity = 0;
    q->max_capacity = max_cap;
    q->list = malloc(sizeof(void *) * LEN);
    return q;
}


//
//
//
void destory(Queue q)
{
    free(q->list);
    free(q);
}


// 
//
// @param:
void enqueue(Queue q, void* item)
{
    if (q->curr_capacity == q->max_capacity)
    {
        dequeue(q);
        // Update queue
    }
    q->list[q->curr_capacity] = item;    
    q->curr_capacity += 1;
}


//
//
// @param:
void dequeue(Queue q)
{

}


//
//
// @param:
void* qfront(Queue q)
{
    return 0;
}


//
//
// @param:
void* qrear(Queue q)
{
    return 0;
}


//
//
// @param:
int is_empty(Queue q)
{
    return 0;
}


// 
//
// @param:
int is_full(Queue q)
{
    return 0;
}


//
//
// @param:
int qlength(Queue q)
{
    return 0; 
}
