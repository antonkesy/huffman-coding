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

void exampleUsage()
{
    //get unsigned char array of data to convert
    char *exampleString = "BCAADDDCCACACAC";
    //create huffman data
    HuffmanData *hd = code_into_huffmanData((unsigned char *)exampleString, strlen(exampleString));
    //need to transfer whole data to decode into original

    //create pointer to unsigned char arrays
    unsigned char **decoded = malloc(sizeof(unsigned char **));
    //if you need size of the original unsigend char arrays
    size_t outputSize;
    //decodes huffman data into decoded
    decode_huffman_data(hd, decoded, &outputSize);
    printf("%s\n", *decoded);
    //done?
    delete_huffman_data(hd);
}

int testHuffman()
{
    //TODO file reading:
    //fread while return not 0
    //do fixed blocks of 16kb or something like that

    char *testString = "Were you able to open it before, on the computer you're using now? XYC23423";
    HuffmanData *hd = code_into_huffmanData((unsigned char *)testString, strlen(testString));
    unsigned char **dest = malloc(sizeof(unsigned char **));
    size_t outputSize = 0;
    decode_huffman_data(hd, dest, &outputSize);
    //dest[outputSize - 2] = '\0';
    printf("%s\n%s\n", testString, *dest);
    size_t compareValue = strcmp(testString, (char *)*dest);
    printf("compare should be 0 = %u", compareValue);
    return compareValue;
}

int testAllChars()
{
    printf("test all chars\n");
    int isError = 0;

    unsigned char *allChars = malloc(0x100);
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

        unsigned char *allCharsDecode = malloc(0x100);
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
    exampleUsage();
    printf("huffman test failed ? %i\n", testHuffman());
    printf("huffman test all chars failed ? %i\n", testAllChars());
    //test_min_heap();

#ifndef DEBUG
    //getchar();
#endif
    return 0;
}
