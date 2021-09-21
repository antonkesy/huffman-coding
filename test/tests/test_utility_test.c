#include "../test_utility.h"

bool is_files_equal_working_un_equal(void) {
    const char *file_1_name = "test1unequal.txt";
    const char *file_2_name = "test2unequal.txt";

    create_test_input_file(file_1_name, 10);
    create_test_input_file(file_2_name, 100);

    FILE *fp1 = fopen(file_1_name, "r");
    FILE *fp2 = fopen(file_2_name, "r");

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
    const char *file_1_name = "test1equal.txt";
    const char *file_2_name = "test2equal.txt";

    create_test_input_file(file_1_name, 0xFFF);
    create_test_input_file(file_2_name, 0xFFF);

    FILE *fp1 = fopen(file_1_name, "r");
    FILE *fp2 = fopen(file_2_name, "r");

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