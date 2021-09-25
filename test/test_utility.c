#include "test_utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../utility/huffman_file_to_file.h"

bool files_equal(const char *file_1_name, const char *file_2_name)
{
    FILE *fp1 = open_file_to_read(file_1_name);
    if (is_file_open_correctly(fp1))
    {
        perror("Unable to open file 1.");
        return false;
    }

    FILE *fp2 = open_file_to_read(file_2_name);
    if (is_file_open_correctly(fp2))
    {
        perror("Unable to open file 2.");
        return false;
    }

    bool are_files_equal = _files_equal(fp1, fp2);

    fclose(fp1);
    fclose(fp2);

    return are_files_equal;
}

bool _files_equal(FILE *fp1, FILE *fp2)
{
    //same files
    if (fp1 == fp2)
    {
        return true;
    }

    char f1_buffer = 0;
    char f2_buffer = 0;
    unsigned int f1_read_bytes = 1;
    unsigned int f2_read_bytes = 1;

    fseek(fp1, 0, SEEK_SET);
    fseek(fp2, 0, SEEK_SET);
    //well ...
    while (f1_read_bytes > 0 && f2_read_bytes > 0)
    {
        f1_read_bytes = fread(&f1_buffer, 1, 1, fp1);
        f2_read_bytes = fread(&f2_buffer, 1, 1, fp2);
        if (f1_buffer != f2_buffer || (f1_read_bytes ^ f2_read_bytes) != 0)
        {
            return false;
        }
    }
    return true;
}

void create_test_input_file(const char *file_name, unsigned int lines)
{
    FILE *fp = open_file_to_write(file_name);
    if (fp != NULL)
    {
        fprintf(fp, "Hello,\tI'm a testing file :)\n");
        for (register unsigned int i = 0; i < lines; ++i)
        {
            fprintf(fp, "number iteration = %i\n", i);
        }
    }
    fclose(fp);
}

void create_test_big_input_file(const char *file_name)
{
    FILE *fp = open_file_to_write(file_name);
    if (fp != NULL)
    {
        fprintf(fp, "Big testing file!\n");
        //7GB
        for (register uint_fast64_t i = 0; i < 0xFFFFFFF; ++i)
        {
            fprintf(fp, "number iteration = %i\n", i);
        }
    }
    fclose(fp);
}
