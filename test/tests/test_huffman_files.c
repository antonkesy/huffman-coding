#include <stdio.h>
#include <stdbool.h>
#include "../test_utility.h"
#include "../../utility/huffman_file_to_file.h"


#define TEST_INPUT_FILE_NAME "input.txt"
#define TEST_CODED_FILE_NAME "coded.txt"
#define TEST_OUTPUT_FILE_NAME "output.txt"


bool test_file_coding(void)
{
    create_test_input_file(TEST_INPUT_FILE_NAME, 0xFFF);
    FILE *src = fopen(TEST_INPUT_FILE_NAME, "rb");
    if (src == NULL || ferror(src))
    {
        printf("Unable to open file.\n");
        return 1;
    }

    FILE *coded_file = fopen(TEST_CODED_FILE_NAME, "wb");
    if (coded_file == NULL || ferror(coded_file))
    {
        printf("Unable to create file.\n");
        return 1;
    }

    huffman_code_file_to_file(src, coded_file);

    fclose(src);
    fclose(coded_file);

    coded_file = fopen(TEST_CODED_FILE_NAME, "rb");
    if (coded_file == NULL || ferror(coded_file))
    {
        printf("Unable to open file.\n");
        return 1;
    }

    FILE *dest = fopen(TEST_OUTPUT_FILE_NAME, "wb+");
    if (dest == NULL || ferror(dest))
    {
        printf("Unable to create file.\n");
        return 1;
    }

    huffman_decode_file_to_file(coded_file, dest);

    fclose(coded_file);

    src = fopen(TEST_INPUT_FILE_NAME, "rb");
    if (src == NULL || ferror(src))
    {
        printf("Unable to open file.\n");
        return 1;
    }


    const bool are_files_equal = files_equal(src, dest);

    fclose(dest);

    return are_files_equal;
}

int main(void)
{
    return !test_file_coding();
}
