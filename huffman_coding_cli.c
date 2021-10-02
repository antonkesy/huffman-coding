#include <string.h>
#include <stdlib.h>
#include <errno.h>
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
                buffer_size = get_buffer_size_from_argument(argv[i]);
                break;
            case InputFileName:
                input_file_name = argv[i] + strlen(InputFileNameArgument);
                break;
            case OutputFileName:
                output_file_name = argv[i] + strlen(OutputFileNameArgument);
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
    printf("upsi dupsi something wrong :/");
}

void print_version()
{
    printf("Huffman coding version ");
    printf(VERSION);
    printf("\n");
}

void print_info()
{
    printf("huffman coding by Anton Kesy\n");
}

long get_argument_long_value(char *arg, int argument_title_length)
{
    return strtol(arg + argument_title_length, NULL, 10);
}

long get_buffer_size_from_argument(char *argument)
{
    long parsed_value = get_argument_long_value(argument, strlen(BufferSizeArgument));
    if (errno == ERANGE)
    {
        perror("buffer size value couldn't be read!");
    }
    if (parsed_value <= 0)
    {
        perror("buffer size value invalid! Setting to default value");
        return BufferSize;
    }
    return parsed_value;
}