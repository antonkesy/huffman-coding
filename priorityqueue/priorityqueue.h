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

priorityque *create_priority_que(compare compareFunction);
void push_priority_que(priorityque *pq, const void *item);
void *peek_priority_que(const priorityque *pq);
void *pop_priority_que(priorityque *pq);
_Bool is_empty_priority_que(const priorityque *pq);
void iterate_priority_que(const priorityque *pq, void (*simple)(void *));
void clear_priority_que(priorityque *pq);
void delete_priority_que(priorityque *pq);

#endif
