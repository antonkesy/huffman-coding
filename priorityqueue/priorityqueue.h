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

typedef int (*compare)(const void *, const void *);

typedef struct
{
    size_t size;
    linkedData *firstItem;
    compare compareFunction;
} priorityque;

priorityque *createPQ(compare compareFunction);
void push(priorityque *pq, const void *item);
void *peek(const priorityque *pq);
void *pop(priorityque *pq);
_Bool isEmpty(const priorityque *pq);
void iterate(const priorityque *pq, void (*simple)(void *));

#endif
