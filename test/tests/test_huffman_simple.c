#include <stdlib.h>
#include <string.h>
#include "../../huffman.h"

int main()
{
   char* test_string = "Were you able to open it before, on the computer you're using now? XYC23423";
   HuffmanData* hd = code_into_huffman_data((unsigned char*)test_string, strlen(test_string));
   unsigned char** dest = (unsigned char**)malloc(sizeof(unsigned char**));
   if (dest == NULL)
   {
      return 1;
   }
   size_t output_size = 0;
   decode_huffman_data(hd, dest, &output_size);
   if (*dest == NULL)
   {
      return 1;
   }
   return strcmp(test_string, (char*)*dest);
}
