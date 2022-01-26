#ifndef _TEST_UTILITY_H
#define _TEST_UTILITY_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#define BIG_FILE_TEST_BUFFER_SIZE 0xFFFFFF
#define FILE_COMPARE_BUFFER_SIZE 0xFFFF

bool files_equal(FILE *fp1, FILE *fp2);

bool filesp_equal(const char *file_1_name, const char *file_2_name);

void create_test_input_file(const char *file_name, unsigned int lines);

void create_test_big_input_file(const char *file_name);

bool exists_file(const char *filename);

#endif
