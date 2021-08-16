#include <string.h>
#include "huffman.h"
//#include "huffman.c"

int main(void)
{
    char *testString = "ABCDEEEEEFG";
    HuffmanData hd = GetHuffmanData(testString, strlen(testString));
    return 0;
}
