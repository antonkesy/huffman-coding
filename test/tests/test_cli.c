#include <stddef.h>
#include "../../huffman_coding_cli.h"

int test_error()
{
    int process_return_value = 0;
    process_return_value += process_input_arguments(0, NULL);
    char *bad_arguments = "nothing :)";
    process_return_value += process_input_arguments(2, &bad_arguments);

    return process_return_value;
}

int main(void)
{
    return 0;
}