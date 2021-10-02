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
    char *input_file_name = argv[0];

    long buffer_size = BUFF_SIZE_FILE;
    char **output_file_name = calloc(1, sizeof(char *));
    if (output_file_name == NULL)
    {
        perror("output file name allocation failed!");
        return 1;
    }
    for (int i = 1; i < argc; ++i)
    {
        printf("%s", argv[i]);
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
            case OutputFileName:
                *output_file_name = malloc(strlen(argv[i] - strlen(OutputFileNameArgument)));
                if (*output_file_name != NULL)
                {
                    *output_file_name = strcpy(*output_file_name, argv[i] + strlen(OutputFileNameArgument));
                } else
                {
                    perror("output file error allocation failed!");
                }
                break;
        }
    }

    if (*output_file_name == NULL)
    {
        if (set_default_output_file_name(output_file_name, input_file_name) != 0)
        {
            return 1;
        }
    }

    huffman_code_file_to_file(input_file_name, *output_file_name, buffer_size);
    free(*output_file_name);
    free(output_file_name);
    return 0;
}

enum ArgumentOptions decode_argument(const char *arg)
{
    if (is_argument_x(remove_leading_whitespaces((char *) arg), BufferSizeArgument))
    {
        return BufferSize;
    }
    if (is_argument_x(remove_leading_whitespaces((char *) arg), OutputFileNameArgument))
    {
        return OutputFileName;
    }
    return Error;
}

void print_argument_error()
{
    errno = EINVAL;
    perror("");
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

bool is_argument_x(const char *arg, const char *argument_def)
{
    return strncmp(arg, argument_def, strlen(argument_def)) == 0;
}

const char *remove_leading_whitespaces(char *in)
{
    if (in != NULL)
    {
        do
        {
            if (*in != ' ' || *in == 0)
            {
                return in;
            }
        }
        while (++in);
    }

    return NULL;
}

int set_default_output_file_name(char **out_output_file_name, const char *input_file_name)
{
    unsigned int input_file_name_length = strlen(input_file_name);
    unsigned int file_ending_length = strlen(FileEnding);
    *out_output_file_name = calloc(1, input_file_name_length + file_ending_length + 1);
    if (*out_output_file_name != NULL)
    {
        strncpy(*out_output_file_name, input_file_name, input_file_name_length);
        strncpy(*out_output_file_name + input_file_name_length, FileEnding, file_ending_length);
        return 0;
    } else
    {
        perror("set default output file name failed");
        return 1;
    }
}