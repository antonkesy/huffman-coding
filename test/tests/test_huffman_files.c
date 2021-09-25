#include <stdbool.h>
#include "../test_utility.h"
#include "../../utility/huffman_file_to_file.h"

bool test_file_coding(void)
{
    const char *input_file = "input_file.txt";
    const char *coded_file = "coded_file.txt";
    const char *output_file = "output_file.txt";

    create_test_input_file(input_file, 0xFFF);
    huffman_code_file_to_file(input_file, coded_file);
    huffman_decode_file_to_file(coded_file, output_file);

    return files_equal(input_file, output_file);
}

bool test_big_file_coding(void)
{
    const char *input_file = "big_input_file.txt";
    const char *coded_file = "big_coded_file.txt";
    const char *output_file = "big_output_file.txt";

    create_test_big_input_file(input_file);
    huffman_code_file_to_file(input_file, coded_file);
    huffman_decode_file_to_file(coded_file, output_file);

    return files_equal(input_file, output_file);
}

int main(void)
{
    return !(test_file_coding() && test_big_file_coding());
}
