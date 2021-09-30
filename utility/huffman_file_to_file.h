#ifndef HUFFMAN_TEST_HUFFMAN_FILE_TO_FILE_H
#define HUFFMAN_TEST_HUFFMAN_FILE_TO_FILE_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#define BUFF_SIZE_FILE 1048576

//code file into new file

void huffman_code_file_to_file(const char *src_file_name, const char *des_coded_file_name);

void huffman_decode_file_to_file(const char *src_coded_file_name, const char *des_file_name);

//files need to be opened in binary mode
void _huffman_code_file_to_file(FILE *src, FILE *des);

void _huffman_decode_file_to_file(FILE *src, FILE *des);

//utility

FILE *open_file_to_write(const char *file_name);

FILE *open_file_to_read(const char *file_name);

bool is_file_open_correctly(FILE *file);

uint64_t get_buffer_size_from_header(FILE *pFile);

void set_buffer_size_header(uint64_t buffer_size, FILE *pFile);

void set_placeholder_buffer_size_header(FILE* pFile);

#endif //HUFFMAN_TEST_HUFFMAN_FILE_TO_FILE_H
