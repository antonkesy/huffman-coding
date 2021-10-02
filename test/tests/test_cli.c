#include <stddef.h>
#include "../../huffman_coding_cli.h"
#include "../test_utility.h"

int test_error()
{
    int process_return_value = 0;
    process_return_value += process_input_arguments(0, NULL);
    char *bad_arguments = "nothing :)";
    process_return_value += process_input_arguments(2, &bad_arguments);

    return process_return_value == 2 ? 0 : 1;
}

int test_buffer_size()
{
    create_test_input_file("testfilename.txt", 0xF);
    int process_return_value = 0;
    char *bad_arguments[] = {"testfilename.txt", "-buffSize=12345"};
    process_return_value += process_input_arguments(2, bad_arguments);

    return process_return_value;
}

int main(void)
{
    return test_error() + test_buffer_size();
}


