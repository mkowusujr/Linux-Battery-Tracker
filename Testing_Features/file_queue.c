// file: queue
// description: a queue of length 5
// author: mathew owusu jr
#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#define LEN 5


// FILE operations
//static char *get_filename(FILE *fileptr)
//{
//    return "TODO";
//}


//
typedef struct queue_s{
    int curr_capacity;
    int max_capacity;
    void** list;
}* Queue;


//
//
// @param:
static void update_bat_stat_log(Queue q)
{
    FILE *bat_log = fopen("bat_log.txt", "w");
    for (int i = 0; i < qlength(q); i++)
    {
        if (i != (qlength(q) - 1))
        {
            fprintf(bat_log, (char*)(q->list[i]));
            fprintf(bat_log, ",");    
        }
        else
        {
            fprintf(bat_log, (char*)(q->list[i]));
            fprintf(bat_log, "\n");
        }
    }
    //fprintf(bat_log,"\n");
    fclose(bat_log);
}


//
//
// @param:
// @return:
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
// @param:
void destory_queue(Queue q)
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
    }
    q->list[q->curr_capacity] = item;    
    q->curr_capacity += 1;
    update_bat_stat_log(q);
}


//
//
// @param:
void dequeue(Queue q)
{
    remove((char*)qfront(q));
    for (int i = 1; i < q->curr_capacity; i++)
    {
        q->list[i-1] = q->list[i];
    }
    q->list[q->curr_capacity - 1]=NULL;
    q->curr_capacity -= 1;
}


//
//
// @param:
// @return:
void* qfront(Queue q)
{
    return q->list[0];
}


//
//
// @param:
// @return: 
void* qrear(Queue q)
{
    return q->list[q->curr_capacity - 1];
}


//
//
// @param:
// @return:
void* qposition(Queue q, int position)
{
    return q->list[position];
}

//
//
// @param:
// @return:
void** get_queue(Queue q)
{
    return q->list;
}


//
//
// @param:
// @return: 1 if empty, 0 if not empty
int is_q_empty(Queue q)
{
    if(q->curr_capacity != 0)
        return 0;
    else 
        return 1;
}


// 
//
// @param:
// @ return 1 if full, 0 is not full
int is_q_full(Queue q)
{
    if (q->curr_capacity != q->max_capacity)
        return 0;
    else
        return 1;
}


//
//
// @param:
// @return:
int qlength(Queue q)
{
    return q->curr_capacity; 
}