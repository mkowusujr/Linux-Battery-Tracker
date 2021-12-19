// file: test_queue.c
// description: Test queue using strings
// author: mathew owusu jr
#include <stdio.h>
#include "queue.h"
void qprint(Queue q)
{
    //printf("%d\n", qlength(q));
    for(int i = 0; i < qlength(q); i++)
    {
        if (i != (qlength(q) - 1))
            printf("%s, ", (char*)qposition(q, i));
        else
            printf("%s\n", (char*)qposition(q, i));
    }
    //printf("\n")
}

int main()
{
    Queue q = make_queue(5);
    enqueue(q, (void*) "Item 1");
    enqueue(q, (void*) "Item 2");
    enqueue(q, (void*) "Item 3");
    enqueue(q, (void*) "Item 4");
    enqueue(q, (void*) "Item 5");
    qprint(q);
    dequeue(q); // item 1 leaves
    qprint(q);
    dequeue(q); // item 2 leaves
    qprint(q);
    dequeue(q); // item 3 leaves
    qprint(q);
    dequeue(q); // item 4 leaves
    qprint(q);
    dequeue(q); // item 5 leaves
    qprint(q);
    printf("%d\n", qlength(q));  
    return 0;
}
