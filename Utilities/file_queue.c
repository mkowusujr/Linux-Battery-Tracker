/// file: file_queue.c
/// description: an implementation of the queue header file that has special
/// functions to handle the functionality of the battery tracking program
/// author: mathew owusu jr
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "queue.h"
#define LOG_FILE "/var/log/battery-tracker/bat_log.txt"

/// A queue struct
/// @param int curr_capacity is the current capacity of the queue
/// @param int max_capacity is the max amount of elements the queue can hold
/// @param void **list a list that simulates the queue
/// @param *buffer needed to track the file pointer to the battery log
/// @returns a pointer to queue struct
typedef struct queue_s{
    int curr_capacity;
    int max_capacity;
    void **list;
    void *buffer;
}* Queue;


/// Opens the battery log file to reflect the filesnames currently in the queue
/// @param Queue q is a pointer to a queue struct
static void update_bat_stat_log(Queue q)
{
    FILE *bat_log = fopen(LOG_FILE, "w");
    for (int i = 0; i < qlength(q); i++)
    {
        if (i != (qlength(q) - 1))
        {
            fprintf(bat_log, "%s,", (char*)(q->list[i]));
        }
        else
        {
            fprintf(bat_log, "%s\n", (char*)(q->list[i]));
        }
    }
    fclose(bat_log);
}

/// Adds the first element into the queue, used to sync the queue with battery
/// log in cases where the program is restarted
/// @param Queue q is a pointer to a queue struct
/// @param void *item is an element that has no type
static void initial_enqueue(Queue q, void*item)
{
    q->list[q->curr_capacity] = item;
    q->curr_capacity += 1;
}

/// Syncs the queue with the contents of the battery log
/// @param Queue q is a pointer to a queue struct
/// @param FILE *log a pointer to the battery log file
static void *refresh_queue(Queue q, FILE *log)
{
    char *buffer = (char*)calloc(700, sizeof(char));
    fread(buffer, sizeof(char), 700, log);
    printf("%s\n", buffer);
    char *token = strtok(buffer, ",");
    while (token != NULL)
    {
        printf("%s\n", token);
        initial_enqueue(q, (void*)token);
        token = strtok(NULL, ",");
    }
    fclose(log);
    return (void *)buffer;
}


/// Creates the queue and returns a pointer to it
/// @param int max_cap is the max amount of elements the queue can hold
/// @return a pointer to the created queue struct
Queue make_queue(int max_cap)
{
    Queue q = malloc(sizeof(struct queue_s));
    q->curr_capacity = 0;
    q->max_capacity = max_cap;
    q->list = malloc(sizeof(void *) * max_cap);
    FILE *log = fopen(LOG_FILE, "r");
    if (log != NULL)
    {
        q->buffer = refresh_queue(q, log);
    }
    else
    {
        mkdir("/var/log/Battery Tracker/", S_IRWXO);
        log = fopen(LOG_FILE, "w");
        fclose(log);
    }
    return q;
}


/// Frees the memory inside the queue struct, and frees the memeory allocated to
/// the queue struct
/// @param Queue q is a pointer to a queue struct
void destory_queue(Queue q)
{
    free(q->list);
    free(q->buffer);
    free(q);
}


/// Adds a generic element into the queue
/// @param Queue q is a pointer to a queue struct
/// @param void *item is an element that has no type
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


/// Remove the first item from the queue
/// @param Queue q is a pointer to a queue struct
/// @param void *item is an element that has no type
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


/// Returns the element at the front of the queue
/// @param Queue q is a pointer to a queue struct
/// @return the first element in the queue
void *qfront(Queue q)
{
    return q->list[0];
}


/// Returns the element at the end of the queue
/// @param Queue q is a pointer to a queue struct
/// @return the last element in the queue
void *qrear(Queue q)
{
    return q->list[q->curr_capacity - 1];
}


/// Returns the element at the specified position
/// @param Queue q is a pointer to a queue struct
/// @param int position is the index
/// @return the element in queue at the specified qposition
void *qposition(Queue q, int position)
{
    return q->list[position];
}


/// @param Queue q is a pointer to a queue struct
/// @return the list inside the queue struct
void **get_queue(Queue q)
{
    return q->list;
}


/// Returns whether or no the list inside the queue struct is empty
/// @param Queue q is a pointer to a queue struct
/// @return 1 if true, 0 if false
int is_q_empty(Queue q)
{
    if(q->curr_capacity != 0)
        return 0;
    else
        return 1;
}


/// Returns whether or no the list inside the queue struct is full
/// @param Queue q is a pointer to a queue struct
/// @return 1 if true, 0 if false
int is_q_full(Queue q)
{
    if (q->curr_capacity != q->max_capacity)
        return 0;
    else
        return 1;
}


/// @param Queue q is a pointer to a queue struct
/// @return the length of the list inside the queue struct
int qlength(Queue q)
{
    return q->curr_capacity;
}
