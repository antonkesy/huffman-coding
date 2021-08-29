#include <stdlib.h>
#include <string.h>
#include "../../huffman.h"

int main()
{
    char *testString = "Were you able to open it before, on the computer you're using now? XYC23423";
    HuffmanData *hd = code_into_huffmanData((unsigned char *)testString, strlen(testString));
    unsigned char **dest = (unsigned char **)malloc(sizeof(unsigned char **));
    size_t outputSize = 0;
    decode_huffman_data(hd, dest, &outputSize);
    size_t compareValue = strcmp(testString, (char *)*dest);
    return compareValue;
}