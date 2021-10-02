#include <string.h>
#include "huffman_coding_cli.h"
#include "utility/huffman_file_to_file.h"


int process_input_arguments(int argc, char **argv)
{
    if (argc <= 1)
    {
        return 1;
    }
    long buffer_size = BUFF_SIZE_FILE;
    char *input_file_name = NULL;
    char *output_file_name = NULL;
    for (int i = 0; i < argc; ++i)
    {
        switch (decode_argument(argv[i]))
        {
            case Error:
                print_argument_error();
                return 1;
            case Version:
                print_version();
                break;
            case Info:
                print_info();
                break;
            case BufferSize:
                buffer_size = get_argument_long_value(argv[i], strlen(BufferSizeArgument));
                break;
            case InputFileName:
                input_file_name = get_argument_string(argv[i], strlen(InputFileNameArgument));
                break;
            case OutputFileName:
                output_file_name = get_argument_string(argv[i], strlen(OutputFileNameArgument));
                break;
        }
    }
    huffman_code_file_to_file(input_file_name, output_file_name, buffer_size);
    return 0;
}

enum ArgumentOptions decode_argument(char *arg)
{
    //perror and break if unknown
    return Error;
}

void print_argument_error()
{

}

void print_version()
{

}

void print_info()
{

}

long get_argument_long_value(char *arg, int argument_title_length)
{
    return 0;
}

char *get_argument_string(char *arg, int argument_title_length)
{
    return 0;
}