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

    huffman_code_file_to_file(TEST_INPUT_FILE_NAME, TEST_CODED_FILE_NAME);

    huffman_decode_file_to_file(TEST_CODED_FILE_NAME, TEST_OUTPUT_FILE_NAME);


    FILE *src = open_file_to_read(TEST_INPUT_FILE_NAME);
    if (src == NULL || ferror(src))
    {
        printf("Unable to open file.\n");
        return 1;
    }

    FILE *dest = open_file_to_read(TEST_OUTPUT_FILE_NAME);
    if (dest == NULL || ferror(dest))
    {
        printf("Unable to create file.\n");
        return 1;
    }

    const bool are_files_equal = files_equal(src, dest);

    fclose(src);
    fclose(dest);

    return are_files_equal;
}

int main(void)
{
    return !test_file_coding();
}
