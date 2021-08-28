#include "test_utility.h"
#include <stdio.h>

int files_equal(FILE *fp1, FILE *fp2)
{
    //same files
    if (fp1 == fp2)
    {
        return 1;
    }

    char f1_buffer = 0;
    char f2_buffer = 0;
    int f1_read_bytes = 1;
    int f2_read_bytes = 1;

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