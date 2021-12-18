// file: test_queue.c
// description: Test queue
// author: mathew owusu jr
#include <stdio.h>
#include "queue.h"

int main()
{
    Queue q = make_queue();
    enqueue(q, (void*) "Item 1");
    printf("%s\n", (char*)qposition(q, 0));
    return 0;
}
