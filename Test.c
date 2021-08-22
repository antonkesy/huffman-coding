#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "huffman.h"
#include "priorityqueue/priorityqueue.h"
#include "priorityqueue/priorityqueuetest.h"
#include "minheap/minheap.h"
#include "minheap/minheaptest.h"
#define DEBUG

int testHuffman()
{
    //TODO file reading:
    //fread while return not 0
    //do fixed blocks of 16kb or something like that

    char *testString = "Were you able to open it before, on the computer you're using now? XYC23423";
    //char *testString = "BCAADDDCCACACAC";
    int lenght = strlen(testString);
    HuffmanData *hd = code_into_huffmanData(testString, strlen(testString));
    char **dest = malloc(sizeof(char **));
    size_t outputSize = 0;
    decode_huffman_data(hd, dest, &outputSize);
    //dest[outputSize - 2] = '\0';
    printf("%s\n%s\n", testString, *dest);
    size_t compareValue = strcmp(testString, *dest);
    printf("compare should be 0 = %u", compareValue);
    return compareValue;
}

int testAllChars()
{
    printf("test all chars\n");
    int isError;

    char *allChars = malloc(0x100);
    if (allChars != NULL)
    {
        for (register int i = 0; i < 0x100; ++i)
        {
            allChars[i] = (char)i;
            //print_char_as_binary(allChars[i]);
            //printf("\n");
        }

        //printf("\n\n");
        HuffmanData *hd = code_into_huffmanData(allChars, 0x100);

        char *allCharsDecode = malloc(0xFF);
        if (allCharsDecode != NULL)
        {
            size_t outputSize = 0;
            decode_huffman_data(hd, &allCharsDecode, &outputSize);
            for (register int i = 0; i < 0x100; ++i)
            {
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
    printf("huffman test failed ? %i\n", testHuffman());
    //printf("huffman test all chars failed ? %i\n", testAllChars());
    //testHeap();

#ifndef DEBUG
    //getchar();
#endif
    return 0;
}
