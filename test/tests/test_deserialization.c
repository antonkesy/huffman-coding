#include <stdlib.h>
#include <string.h>
#include "../../huffman.h"

int main(void)
{
   char* example_string = "BCAADDDCCACACAC";
   HuffmanData* hd = code_into_huffman_data((unsigned char*)example_string, strlen(example_string));
   unsigned char** serialization = (unsigned char**)malloc(sizeof(unsigned char**));
   if (serialization == NULL)
   {
      return 1;
   }
   serialize_huffman_data(hd, serialization);
   if (*serialization == NULL)
   {
      return 1;
   }
   size_t bytes_for_data = 0U;
   HuffmanData* hd_de_serial = deserialize_huffman_data(*serialization, &bytes_for_data);
   if (hd_de_serial == NULL)
   {
      return 1;
   }
   if (hd->bits != hd_de_serial->bits)
   {
      printf("bits not same!\n");
      return 1;
   }
   for (int i = 0; i < hd->sort_items->size; ++i)
   {
      printf("%i %i\n", hd->sort_items->items[i].freq, hd->sort_items->items[i].value);
      if (hd->sort_items->items[i].freq != hd->sort_items->items[i].value)
      {
         //not same value!
         return 1;
      }
   }

   free(serialization);
   serialization = NULL;
   delete_huffman_data(hd);
   hd = NULL;
   delete_huffman_data(hd_de_serial);
   hd_de_serial = NULL;
   return 0;
}