#include <stdlib.h>
#include "../../src/huffman.h"

int main(void)
{
    bool is_test_correct = true;

    uint8_t *all_chars = (uint8_t *) malloc(0x100);
    if (all_chars != NULL)
    {
        for (register uint32_t i = 0; i < 0x100; ++i)
        {
            all_chars[i] = (uint8_t) i;
        }

        HuffmanData *hd = code_into_huffman_data(all_chars, 0x100);

        uint8_t *allCharsDecode = NULL;
        if (hd != NULL)
        {
            uint32_t outputSize = 0;
            decode_huffman_data(hd, &allCharsDecode, &outputSize);
            for (register uint32_t i = 0; i < 0x100; ++i)
            {
                if (all_chars[i] != allCharsDecode[i])
                {
                    perror("all char error");
                    is_test_correct = false;
                }
            }
        } else
        {
            is_test_correct = false;
        }
        free(allCharsDecode);
        delete_huffman_data(hd);
    } else
    {
        perror("malloc error");
        is_test_correct = false;
    }

    free(all_chars);

    return !is_test_correct;
}
