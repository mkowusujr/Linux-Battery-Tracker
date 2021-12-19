// file: test_queue.c
// description: Test queue using strings
// author: mathew owusu jr
#include <stdio.h>
#include "queue.h"
void qprint(Queue q)
{
    for(int i = 0; i < qlength(q); i++)
    {
        if (i != (qlength(q) - 1))
            printf("%s, ", (char*)qposition(q, i));
        else
            printf("%s\n", (char*)qposition(q, i));
    }
}

int main()
{
    Queue q = make_queue(5);
    
    // Test enqueue and dequeue and qlength
    printf("Test enqueue\nAdding five items...\n");
    enqueue(q, (void*) "Item 1");
    enqueue(q, (void*) "Item 2");
    enqueue(q, (void*) "Item 3");
    enqueue(q, (void*) "Item 4");
    enqueue(q, (void*) "Item 5");
    qprint(q);
    printf("\nTest dequeue\n");
    dequeue(q); // item 1 leaves
    printf("dequeuing... current queue is now: ");
    qprint(q);
    dequeue(q); // item 2 leaves
    printf("dequeuing... current queue is now: ");     
    qprint(q);
    dequeue(q); // item 3 leaves
    printf("dequeuing... current queue is now: ");     
    qprint(q);
    dequeue(q); // item 4 leaves
    printf("dequeuing... current queue is now: ");     
    qprint(q);
    dequeue(q); // item 5 leaves
    printf("dequeuing... current queue is now: ");     
    qprint(q);
    printf("Current length: %d\n", qlength(q));  

    // Test empty and full
    printf("\nTest empty and full functions\nThe queue is currently ");
    if (is_q_empty(q))
    {
        printf("empty");
    }
    else
        printf("not empty");
    printf(" and it is also ");
    if (is_q_full(q))
    {
        printf("full\n");
    }
    else
        printf("not full\n");

    // front and rear
    printf("\nTest qfront and qrear\nAdding five more items...\n");
    enqueue(q, (void*) "Item 6");
    enqueue(q, (void*) "Item 7");
    enqueue(q, (void*) "Item 8");
    enqueue(q, (void*) "Item 9");
    enqueue(q, (void*) "Item 10");    
    printf("first in line is: %s\n", (char*)qfront(q));
    printf("last in line is: %s\n", (char*)qrear(q));
    
    // Testing auto queue when at max cap
    printf("\nTest auto queue when at max cap\n");
    printf("Adding item...\n"); // Add item
    enqueue(q, (void*) "Item 11");
    printf("first in line is: %s\n", (char*)qfront(q));
    printf("last in line is: %s\n", (char*)qrear(q));
    printf("Adding item...\n"); // Add item
    enqueue(q, (void*) "Item 12");
    printf("first in line is: %s\n", (char*)qfront(q));
    printf("last in line is: %s\n", (char*)qrear(q));
    printf("Adding item...\n"); // Add item
    enqueue(q, (void*) "Item 13");
    printf("first in line is: %s\n", (char*)qfront(q));
    printf("last in line is: %s\n", (char*)qrear(q));

    // free memory
    destory_queue(q);
    return 0;
}
