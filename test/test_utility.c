#include "test_utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <memory.h>
#include "../src/utility/huffman_file_to_file.h"


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

    uint8_t *f1_buffer = malloc(FILE_COMPARE_BUFFER_SIZE);
    uint8_t *f2_buffer = malloc(FILE_COMPARE_BUFFER_SIZE);
    if (f1_buffer == NULL || f2_buffer == NULL)
    {
        perror("malloc compare buffer failed");
        return false;
    }
    size_t f1_read_bytes = 1U;
    size_t f2_read_bytes = 1U;

    fseek(fp1, 0, SEEK_SET);
    fseek(fp2, 0, SEEK_SET);
    //well ...
    while (f1_read_bytes > 0U && f2_read_bytes > 0U)
    {
        f1_read_bytes = fread(f1_buffer, FILE_COMPARE_BUFFER_SIZE, 1, fp1);
        f2_read_bytes = fread(f2_buffer, FILE_COMPARE_BUFFER_SIZE, 1, fp2);
        if ((f1_read_bytes | f2_read_bytes) != 0 || memcmp(f1_buffer, f2_buffer, f1_read_bytes) != 0)
        {
            free(f1_buffer);
            free(f2_buffer);
            return false;
        }
    }
    free(f1_buffer);
    free(f2_buffer);
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
        uint8_t *data = malloc(BIG_FILE_TEST_BUFFER_SIZE);
        if (data != NULL)
        {
            for (uint32_t i = 0U; i < (uint32_t) BIG_FILE_TEST_BUFFER_SIZE; ++i)
            {
                data[i] = (uint8_t) i;
            }
            fprintf(fp, "Big testing file!\n");
            for (register uint_fast64_t i = 0; i < 0xFF; ++i)
            {
                fwrite(data, BIG_FILE_TEST_BUFFER_SIZE, 1, fp);
            }
        }
    }
    fclose(fp);
}

bool exists_file(const char *filename)
{
    FILE *file;
    if ((file = fopen(filename, "r")))
    {
        fclose(file);
        return true;
    }

    return false;
}