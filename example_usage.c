#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "src/huffman.h"
#include "test/test_utility.h"
#include "src/utility/huffman_file_to_file.h"

#define TEST_INPUT_FILE_NAME "input.txt"
#define TEST_CODED_FILE_NAME "coded.txt"
#define TEST_OUTPUT_FILE_NAME "output.txt"

void example_usage_files(void)
{
    create_test_input_file(TEST_INPUT_FILE_NAME, 0xFFF);

    huffman_code_file_to_file(TEST_INPUT_FILE_NAME, TEST_CODED_FILE_NAME, BUFF_SIZE_FILE);

    huffman_decode_file_to_file(TEST_CODED_FILE_NAME, TEST_OUTPUT_FILE_NAME);
}

void example_usage(void)
{
    //get unsigned char array of data to convert
    uint8_t* example_string = (uint8_t*) "BCAADDDCCACACAC";
    //get size of input data
    const uint32_t size_string = strlen((char*) example_string);
    //create huffman data
    HuffmanData* hd = code_into_huffman_data(example_string, size_string);
    //need to transfer whole data to decode into original

    //create pointer to unsigned char arrays
    uint8_t** decoded = (uint8_t**) malloc(sizeof(uint8_t**));
    if (decoded != NULL)
    {
        //if you need size of the original uint8_t array
        uint32_t output_size;
        //decodes huffman data into into original uint8_t input
        decode_huffman_data(hd, decoded, &output_size);
        if (*decoded != NULL)
        {
            for (size_t i = 0U; i < output_size; ++i)
            {
                printf("%c", (*decoded)[i]);
            }
            printf("\n");
        } else
        {
            printf("decoded is null!\n");
        }
        //done?
        delete_huffman_data(hd);
        free(*decoded);
        free(decoded);
    }
}

int main(void)
{
    example_usage();
    example_usage_files();
    return 0;
}
