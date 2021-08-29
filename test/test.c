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



int test_deserialisation()
{
    char *exampleString = "BCAADDDCCACACAC";
    HuffmanData *hd = code_into_huffmanData((unsigned char *)exampleString, strlen(exampleString));
    unsigned char **serialization = (unsigned char **)malloc(sizeof(unsigned char **));
    serialize_huffmandata(hd, serialization);
    size_t bytes_for_data = 0U;
    HuffmanData *hdDeSeri = deserialize_huffmandata(*serialization, &bytes_for_data);

    if (hd->bits == hdDeSeri->bits)
    {
        printf("bits same!\n");
    }
    for (int i = 0; i < hd->sort_items->size; ++i)
    {
        printf("%i %i\n", hd->sort_items->items[i].freq, hd->sort_items->items[i].value);
    }
    return 0;
}

int testHuffman()
{
    //TODO file reading:
    //fread while return not 0
    //do fixed blocks of 16kb or something like that

    char *testString = "Were you able to open it before, on the computer you're using now? XYC23423";
    HuffmanData *hd = code_into_huffmanData((unsigned char *)testString, strlen(testString));
    unsigned char **dest = (unsigned char **)malloc(sizeof(unsigned char **));
    size_t outputSize = 0;
    decode_huffman_data(hd, dest, &outputSize);
    //dest[outputSize - 2] = '\0';
    printf("%s\n%s\n", testString, *dest);
    size_t compareValue = strcmp(testString, (char *)*dest);
    printf("compare should be 0 = %u", compareValue);
    return compareValue;
}

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
