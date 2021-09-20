#include <stdio.h>
#include "../test_utility.h"
#include "../../utility/huffman_file_to_file.h"


#define TEST_INPUT_FILE_NAME "input.txt"
#define TEST_CODED_FILE_NAME "coded.txt"
#define TEST_OUTPUT_FILE_NAME "output.txt"


int test_file_coding(void) {
    create_test_input_file(TEST_INPUT_FILE_NAME);
    FILE *src = fopen(TEST_INPUT_FILE_NAME, "r");

    if (src == NULL) {
        printf("Unable to open file.\n");
        return 1;
    }

    FILE *coded_file = fopen(TEST_CODED_FILE_NAME, "w");
    if (coded_file == NULL) {
        printf("Unable to create file.\n");
        return 1;
    }

    huffman_code_file_to_file(src, coded_file);

    fclose(src);
    fclose(coded_file);

    coded_file = fopen(TEST_CODED_FILE_NAME, "r");
    if (coded_file == NULL) {
        printf("Unable to open file.\n");
        return 1;
    }

    FILE *dest = fopen(TEST_OUTPUT_FILE_NAME, "w");
    if (dest == NULL) {
        printf("Unable to create file.\n");
        return 1;
    }

    huffman_decode_file_to_file(coded_file, dest);

    const int ret_val = files_equal(coded_file, dest);

    fclose(coded_file);
    fclose(dest);

    return ret_val;
}

int main(void) {
    return test_file_coding();
}
