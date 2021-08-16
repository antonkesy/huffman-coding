#include "huffman.h"
#include <stdio.h>
#include <stdlib.h>

int SortItemComparator(const void *first, const void *second)
{
    return (*(unsigned int *)first) - (*(unsigned int *)second);
}

SortedItems SortItemsByFrequency(char *items, unsigned int size)
{
    unsigned int *freqOfPosition = calloc(0xFF, sizeof(unsigned int));
    register unsigned int uniqueCharsCount = 0U;

    if (freqOfPosition != NULL)
    {
        for (register unsigned int i = 0U; i < size; ++i)
        {
            if (freqOfPosition[items[i]]++ == 0)
            {
                ++uniqueCharsCount;
            }
        }

        SortItem *sortItems = malloc(sizeof(SortItem) * uniqueCharsCount);
        if (sortItems != NULL)
        {
            register unsigned int i = 0U;
            for (register unsigned int j = 0U; j < 0xFF; ++j)
            {
                if (freqOfPosition[j] != 0)
                {
                    sortItems[i].value = j;
                    sortItems[i].freq = freqOfPosition[j];
                    ++i;
                }
            }
        }
        else
        {
            printf("malloc error");
        }

        qsort(sortItems, uniqueCharsCount, sizeof(SortItem), SortItemComparator);

        for (int i = 0; i < uniqueCharsCount; ++i)
        {
            printf("%c %u\n", sortItems[i].value, sortItems[i].freq);
        }
        //free(sortItems);
        //TODO: create heap of sorted Items
    }
    else
    {
        //MALLOC ERROR
        printf("malloc error");
    }
    free(freqOfPosition);
}

HuffmanData GetHuffmanData(char *items, unsigned int size)
{
    SortItemsByFrequency(items, size);
}

Heap GetHuffmanHeap(char *items, unsigned int *freq, unsigned int size)
{
}
