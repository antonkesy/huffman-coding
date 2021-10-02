#ifndef HUFFMAN_HUFFMAN_CODING_CLI_H
#define HUFFMAN_HUFFMAN_CODING_CLI_H

#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include "utility/huffman_file_to_file.h"

#define CodeArgument "-c"
#define DeCodeArgument "-d"
#define BufferSizeArgument "-buffSize="
#define OutputFileNameArgument "-out="

#define FileEnding ".hc"

enum ArgumentOptions
{
    Error = 0, Version, Info, BufferSize, OutputFileName, CodeMode, DecodeMode
};

int process_input_arguments(int argc, char **argv);

enum ArgumentOptions decode_argument(const char *arg);

void print_argument_error();

void print_version();

void print_info();

long get_argument_long_value(char *arg, int argument_title_length);

long get_buffer_size_from_argument(char *argument);

bool is_argument_x(const char *arg, const char *argument_def);

const char *remove_leading_whitespaces(char *in);

int set_default_output_file_name(char **out_output_file_name, const char *input_file_name);

#endif //HUFFMAN_HUFFMAN_CODING_CLI_H
