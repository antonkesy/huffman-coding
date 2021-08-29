#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "../huffman.h"
#include "../minheap/minheap.h"
#include "../minheap/minheaptest.h"
#include "test_utility.h"
#include "../utility/huffman_utility.h"
#include "huffman_utility_test.h"

#define DEBUG







int test_all_chars()
{
    printf("test all chars\n");
    int isError = 0;

    unsigned char *allChars = (unsigned char *)malloc(0x100);
    if (allChars != NULL)
    {
        for (register int i = 0; i < 0x100; ++i)
        {
            allChars[i] = (unsigned char)i;
            //print_char_as_binary(allChars[i]);
            //printf("\n");
        }

        //printf("\n\n");
        HuffmanData *hd = code_into_huffmanData(allChars, 0x100);

        unsigned char *allCharsDecode = (unsigned char *)malloc(0x100);
        if (allCharsDecode != NULL)
        {
            size_t outputSize = 0;
            decode_huffman_data(hd, &allCharsDecode, &outputSize);
            for (register int i = 0; i < 0x100; ++i)
            {
                /*
                printf("was = ");
                print_char_as_binary(allChars[i]);
                printf("\tshould = ");
                print_char_as_binary(allCharsDecode[i]);
                printf("\n");*/
                if (allChars[i] != allCharsDecode[i])
                {
                    isError = 1;
                }
            }
        }
        else
        {
            isError = 1;
        }
    }
    else
    {
        //malloc error
        isError = 1;
    }

    //free(allChars);
    return isError;
}

int main(void)
{
    //TODO split tests for automated testing
    //test_equal_sort_item();
    //test_equal_sorted_items();
    //test_is_huffman_data_equal();
    //printf("huffman test failed ? %i\n", testHuffman());
    //printf("huffman test all chars failed ? %i\n", test_all_chars());
    //test_serialization();
    //test_deserialisation();
    //test_min_heap();
    //heap_test_range();
    //heap_test_huffman_nodes();

#ifndef DEBUG
    //getchar();
#endif
    return 0;
}
