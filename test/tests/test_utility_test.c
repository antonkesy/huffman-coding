#include "../test_utility.h"

#define FILE_1_NAME "test1.txt"
#define FILE_2_NAME "test2.txt"

bool is_files_equal_working_un_equal(void) {
    create_test_input_file(FILE_1_NAME, 10);
    create_test_input_file(FILE_2_NAME, 100);

    FILE *fp1 = fopen(FILE_1_NAME, "r");
    FILE *fp2 = fopen(FILE_2_NAME, "r");

    bool is_un_equal = false;

    if (fp1 != NULL && fp2 != NULL) {
        if (!files_equal(fp1, fp2)) {
            is_un_equal = true;
        }
    }
    fclose(fp1);
    fclose(fp2);
    return is_un_equal;
}

bool is_files_equal_working_equals(void) {
    create_test_input_file(FILE_1_NAME, 0xFFF);
    create_test_input_file(FILE_2_NAME, 0xFFF);

    FILE *fp1 = fopen(FILE_1_NAME, "r");
    FILE *fp2 = fopen(FILE_2_NAME, "r");

    bool is_equal = true;

    if (fp1 != NULL && fp2 != NULL) {
        if (!files_equal(fp1, fp2)) {
            is_equal = false;
        }
    }
    fclose(fp1);
    fclose(fp2);
    return is_equal;
}

int main(void) {
    return (is_files_equal_working_equals() && is_files_equal_working_un_equal()) ? 0 : 1;
}