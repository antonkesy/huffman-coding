#ifndef _TEST_UTILITY_H
#define _TEST_UTILITY_H

#include <stdio.h>
#include <stdbool.h>

bool files_equal(FILE* fp1, FILE* fp2);
void create_test_input_file(const char* file_name);

#endif
