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
    //printf("%d\n", qlength(q));
    enqueue(q, (void*) "Item 1");
    //printf("%d\n", qlength(q));
    //qprint(q);
    enqueue(q, (void*) "Item 2");
    //printf("%d\n", qlength(q));
    enqueue(q, (void*) "Item 3");
    //printf("%d\n", qlength(q));
    enqueue(q, (void*) "Item 4");
    enqueue(q, (void*) "Item 5");
    //printf("%d\n", qlength(q));
    qprint(q);

    return 0;
}
