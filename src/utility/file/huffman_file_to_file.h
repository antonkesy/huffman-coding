#ifndef HUFFMAN_TEST_HUFFMAN_FILE_TO_FILE_H
#define HUFFMAN_TEST_HUFFMAN_FILE_TO_FILE_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "../../../include/huffman.h"

#define BUFF_SIZE_FILE (4096*8)

//files need to be opened in binary mode
int huffman_code_file_to_file_p(FILE *src, FILE *des, long buffer_size);

int huffman_decode_file_to_file_p(FILE *src, FILE *des);

//utility

FILE *open_file_to_write(const char *file_name);

FILE *open_file_to_read(const char *file_name);

bool is_file_open_correctly(FILE *file);

uint64_t get_buffer_size_from_header(FILE *pFile);

void set_buffer_size_header(uint64_t buffer_size, FILE *pFile);

void set_placeholder_buffer_size_header(FILE *pFile);

uint64_t fseek64(FILE *pFile, int64_t offset, int origin);

#endif //HUFFMAN_TEST_HUFFMAN_FILE_TO_FILE_H
