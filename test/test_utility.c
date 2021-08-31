#include "test_utility.h"
#include <stdio.h>
#include <stdlib.h>

int files_equal(FILE* fp1, FILE* fp2)
{
   //same files
   if (fp1 == fp2)
   {
      return 1;
   }

   char f1_buffer = 0;
   char f2_buffer = 0;
   unsigned int f1_read_bytes = 1;
   unsigned int f2_read_bytes = 1;

   fseek(fp1, 0, SEEK_SET);
   fseek(fp2, 0, SEEK_SET);

   //well ...
   while (f1_read_bytes > 0)
   {
      f1_read_bytes = fread(&f1_buffer, 1, 1, fp1);
      f2_read_bytes = fread(&f2_buffer, 1, 1, fp2);
      if (f1_buffer != f2_buffer || (f1_read_bytes ^ f2_read_bytes) != 0)
      {
         return 0;
      }
   }
   return 1;
}

void create_test_input_file(const char* file_name)
{
   FILE** fp = malloc(sizeof(FILE**));
   if (fp != NULL) {
      fopen_s(fp, file_name, "w+");
      if (*fp != NULL) {

         if (fp != NULL)
         {
            fprintf(*fp, "Hello,\tI'm a testing file :)\n");
            for (register int i = 0; i < 100; ++i)
            {
               fprintf(*fp, "number iteration = %i\n", i);
            }
         }
         fclose(*fp);
      }
   }
}
