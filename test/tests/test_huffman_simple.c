#include <stdlib.h>
#include <string.h>
#include "../../src/huffman.h"
#include "../../src/utility/huffman_utility.h"

int main()
{
    char *test_string = "Were you able to open it before, on the computer you're using now? XYC23423";
    HuffmanData *hd = code_into_huffman_data((uint8_t *) test_string, strlen(test_string));
    uint8_t **dest = (uint8_t **) malloc(sizeof(uint8_t **));
    if (dest == NULL)
    {
        return 1;
    }
    uint32_t output_size = 0;
    decode_huffman_data(hd, dest, &output_size);
    delete_huffman_data(hd);
    if (*dest == NULL)
    {
        return 1;
    }
    int is_test_correct = !uint8_cmp((uint8_t *) test_string, (uint8_t *) *dest, strlen(test_string));
    free(*dest);
    free(dest);
    return is_test_correct;
}
