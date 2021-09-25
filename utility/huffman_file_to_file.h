#ifndef HUFFMAN_TEST_HUFFMAN_FILE_TO_FILE_H
#define HUFFMAN_TEST_HUFFMAN_FILE_TO_FILE_H

#include <stdio.h>

#define BUFFSIZE_FILE 16384

//code file into new file
void huffman_code_file_to_file(FILE* src, FILE* des);
void huffman_decode_file_to_file(FILE* src, FILE* des);

#endif //HUFFMAN_TEST_HUFFMAN_FILE_TO_FILE_H
