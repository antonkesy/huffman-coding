#include <stdlib.h>
#include <string.h>
#include "../../huffman.h"

int main(void)
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
        free(allCharsDecode);
        delete_huffman_data(hd);
    }
    else
    {
        //malloc error
        isError = 1;
    }

    free(allChars);

    return isError;
}