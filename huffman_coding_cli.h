#ifndef HUFFMAN_HUFFMAN_CODING_CLI_H
#define HUFFMAN_HUFFMAN_CODING_CLI_H

#define BufferSizeArgument "-buffSize="
#define InputFileNameArgument ""
#define OutputFileNameArgument "-out="

enum ArgumentOptions
{
    Error = 0, Version, Info, BufferSize, InputFileName, OutputFileName
};

int process_input_arguments(int argc, char **argv);

enum ArgumentOptions decode_argument(char *arg);

void print_argument_error();

void print_version();

void print_info();

long get_argument_long_value(char *arg, int argument_title_length);

char *get_argument_string(char *arg, int argument_title_length);

#endif //HUFFMAN_HUFFMAN_CODING_CLI_H
