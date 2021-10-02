#include <stddef.h>
#include "../../huffman_coding_cli.h"
#include "../test_utility.h"

int test_error()
{
    int process_return_value = 0;
    process_return_value += process_input_arguments(0, NULL);
    char *bad_arguments = "nothing :)";
    process_return_value += process_input_arguments(1, &bad_arguments);

    return process_return_value == 2 ? 0 : 1;
}

int test_buffer_size()
{
    char *test_file_name = "testfilename.txt";
    create_test_input_file(test_file_name, 0xF);
    int process_return_value = 0;
    char *buffer_arguments[] = {test_file_name, "-buffSize=12345"};
    process_return_value += process_input_arguments(2, buffer_arguments);


    return process_return_value;
}

int test_output_file()
{
    int process_return_value = 0;

    char *test_file_name_input = "testfilename1.txt";
    char *test_file_name = "testfilename1_decoded.txt";
    create_test_input_file(test_file_name_input, 0xFF);
    huffman_code_file_to_file(test_file_name_input, test_file_name, BUFF_SIZE_FILE);


    char *output_file_arguments[] = {test_file_name, "-out=out_file.txt"};
    process_return_value += process_input_arguments(2, output_file_arguments);

    return process_return_value;
}

int test_file_name()
{
    int process_return_value = 0;

    char *test_file_name = "testfilename.txt";

    char *output_file_arguments[] = {test_file_name};
    process_return_value += process_input_arguments(1, output_file_arguments);

    return process_return_value;
}

int main(void)
{
    return test_output_file();
    return test_error() + test_file_name() + test_buffer_size() + test_output_file();
}


