#include <stdio.h>
#include <string.h>
#include "huffman.h"

int main(void)
{
    char *testString = "ABCDEEEEEFG";
    HuffmanData hd = GetHuffmanData(testString, strlen(testString));
    getchar();
    //TODO makefile
    return 0;
}
