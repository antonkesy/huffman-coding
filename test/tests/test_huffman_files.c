#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../huffman.h"
#include "../test_utility.h"

#define TEST_INPUT_FILE_NAME "input.txt"
#define TEST_CODED_FILE_NAME "coded.txt"
#define TEST_OUTPUT_FILE_NAME "output.txt"

void create_test_input_file()
{
    FILE *fp;
    fp = fopen(TEST_INPUT_FILE_NAME, "w+");
    if (fp != NULL)
    {
        fprintf(fp, "Hello,\tI'm a testing file :)\n");
        for (register int i = 0; i < 100; ++i)
        {
            fprintf(fp, "number iteration = %i\n", i);
        }
    }
    fclose(fp);
}

int test_file_coding()
{
    create_test_input_file();
    FILE *src = fopen(TEST_INPUT_FILE_NAME, "r");
    if (src == NULL)
    {
        printf("Unable to open file.\n");
        return 1;
    }

    FILE *codedFile = fopen(TEST_CODED_FILE_NAME, "w");
    if (codedFile == NULL)
    {
        printf("Unable to create file.\n");
        return 1;
    }

    huffman_code_file_to_file(src, codedFile);

    fclose(src);
    fclose(codedFile);

    codedFile = fopen(TEST_CODED_FILE_NAME, "r");
    if (codedFile == NULL)
    {
        printf("Unable to open file.\n");
        return 1;
    }

    FILE *dest = fopen(TEST_OUTPUT_FILE_NAME, "w");
    if (dest == NULL)
    {
        printf("Unable to create file.\n");
        return 1;
    }

    huffman_decode_file_to_file(codedFile, dest);

    int ret_val = files_equal(codedFile, dest);

    fclose(codedFile);
    fclose(dest);

    return ret_val;
}

int main(void)
{
    return test_file_coding();
}