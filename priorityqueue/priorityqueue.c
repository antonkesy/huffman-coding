#include "priorityqueue.h"
#include <stdlib.h>

priorityque *createPQ(compare compareFunction)
{
    priorityque *pq = (priorityque *)malloc(sizeof(priorityque));
    if (pq != NULL && compareFunction != NULL)
    {
        pq->size = 0;
        pq->firstItem = NULL;
        pq->compareFunction = compareFunction;
    }
    return pq;
}

void push(priorityque *pq, void *item)
{
    if (pq->firstItem == NULL)
    {
        pq->firstItem = (linkedData *)malloc(sizeof(linkedData));
        pq->firstItem->data = item;
        pq->firstItem->next = NULL;
    }
    else
    {
        //TODO move edge case into normal iteration
        if (pq->compareFunction(item, pq->firstItem->data) < 0)
        {
            linkedData *old = pq->firstItem;
            pq->firstItem = (linkedData *)malloc(sizeof(linkedData));
            pq->firstItem->data = item;
            pq->firstItem->next = old;
        }
        else
        {
            linkedData *lastItem = pq->firstItem;
            while (lastItem->next != NULL && pq->compareFunction(item, lastItem->next->data) > 0)
            {
                lastItem = lastItem->next;
            }
            if (lastItem->next == NULL)
            {
                lastItem->next = (linkedData *)malloc(sizeof(linkedData));
                lastItem->next->data = item;
                lastItem->next->next = NULL;
            }
            else
            {
                linkedData *newItem = (linkedData *)malloc(sizeof(linkedData));
                newItem->data = item;
                linkedData *next = lastItem->next;
                newItem->next = next;
                lastItem->next = newItem;
            }
        }
    }
    ++pq->size;
}
void *peek(priorityque *pq)
{
    if (isEmpty(pq))
    {
        return NULL;
    }
    return pq->firstItem->data;
}

void *pop(priorityque *pq)
{
    if (isEmpty(pq))
    {
        return NULL;
    }

    linkedData *item = pq->firstItem;
    if (item->next != NULL)
    {
        pq->firstItem = item->next;
    }
    --(pq->size);
    return item->data;
}

_Bool isEmpty(priorityque *pq)
{
    return (pq->size == 0) ? true : false;
}

void iterate(priorityque *pq, void (*simple)(void *))
{
    linkedData *item = pq->firstItem;
    while (item != NULL)
    {
        simple(item->data);
        item = item->next;
    }
}