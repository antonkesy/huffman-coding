#include "../test_utility.h"

#define FILE_1_NAME "test1.txt"
#define FILE_2_NAME "test2.txt"

bool is_files_equal_working(void) {
    create_test_input_file(FILE_1_NAME);
    create_test_input_file(FILE_2_NAME);

    FILE *fp1 = fopen(FILE_1_NAME, "r");
    FILE *fp2 = fopen(FILE_2_NAME, "r");

    if (fp1 != NULL && fp2 != NULL) {
        if (!files_equal(fp1, fp2)) {
            return false;
        }
    } else {
        return false;
    }
    return true;
}

int main(void) {
    return is_files_equal_working() ? 0 : 1;
}