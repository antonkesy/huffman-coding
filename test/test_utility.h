#ifndef _TEST_UTILITY_H
#define _TEST_UTILITY_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

bool _files_equal(FILE *fp1, FILE *fp2);

bool files_equal(const char *file_1_name, const char *file_2_name);

void create_test_input_file(const char *file_name, unsigned int lines);

void create_test_big_input_file(const char *file_name);

bool exists_file(const char *filename);

bool are_buffer_equal(const uint8_t *buffer1, const uint8_t *buffer2, size_t length);

#endif
