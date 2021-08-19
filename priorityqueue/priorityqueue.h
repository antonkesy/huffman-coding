#ifndef PRIORITYQUEUE_H

#define PRIORITYQUEUE_H

#include <stddef.h>
#include <stdbool.h>

/*
pretty basic and unoptimized linked list as prioriyqueue 
*/

struct data
{
    struct data *next;
    void *data;
};

typedef struct data linkedData;

typedef int (*compare)(void *, void *);

typedef struct
{
    size_t size;
    linkedData *firstItem;
    compare compareFunction;
} priorityque;

priorityque *createPQ(compare compareFunction);
void push(priorityque *pq, void *item);
void *peek(priorityque *pq);
void *pop(priorityque *pq);
_Bool isEmpty(priorityque *pq);
void iterate(priorityque *pq, void (*simple)(void *));

#endif
