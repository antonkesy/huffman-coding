#include <stdlib.h>
#include "../../huffman.h"

int main(void)
{
   printf("test all chars\n");
   int is_error = 0;

   unsigned char* all_chars = (unsigned char*)malloc(0x100);
   if (all_chars != NULL)
   {
      for (register int i = 0; i < 0x100; ++i)
      {
         all_chars[i] = (unsigned char)i;
         //print_8bit_as_binary(allChars[i]);
         //printf("\n");
      }

      //printf("\n\n");
      HuffmanData* hd = code_into_huffman_data(all_chars, 0x100);

      unsigned char* allCharsDecode = (unsigned char*)malloc(0x100);
      if (allCharsDecode != NULL && hd!=NULL)
      {
         size_t outputSize = 0;
         decode_huffman_data(hd, &allCharsDecode, &outputSize);
         for (register int i = 0; i < 0x100; ++i)
         {
            /*
            printf("was = ");
            print_char_as_binary(allChars[i]);
            printf("\tshould = ");
            print_8bit_as_binary(allCharsDecode[i]);
            printf("\n");*/
            if (all_chars[i] != allCharsDecode[i])
            {
               is_error = 1;
            }
         }
      }
      else
      {
         is_error = 1;
      }
      free(allCharsDecode);
      delete_huffman_data(hd);
   }
   else
   {
      //malloc error
      is_error = 1;
   }

   free(all_chars);

   return is_error;
}
