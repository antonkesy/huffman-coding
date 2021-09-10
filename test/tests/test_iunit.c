#include "../../utility/independent_int.h"
#include <stdint.h>

int test_iunit_16_value(uint16_t test_value) {
    iuint_16_t test_iunit = *fill_iuint_16(&test_value);
    uint16_t copy_test_value = *get_iuint_16_value(&test_iunit);
    return test_value != copy_test_value;
}

int test_iunit_16(void) {
    int test_sum = 0U;
    test_sum += test_iunit_16_value(0U);
    test_sum += test_iunit_16_value(0xFF);
    test_sum += test_iunit_16_value(0xFFFF);
    test_sum += test_iunit_16_value(0x1234);
    test_sum += test_iunit_16_value(0x4273);
    return test_sum;
}

int test_iunit_32_value(uint32_t test_value) {
    iuint_32_t test_iunit = *fill_iuint_32(&test_value);
    uint32_t copy_test_value = *get_iuint_32_value(&test_iunit);
    return test_value != copy_test_value;
}

int test_iunit_32(void) {
    int test_sum = 0U;
    test_sum += test_iunit_32_value(0U);
    test_sum += test_iunit_32_value(0xFF);
    test_sum += test_iunit_32_value(0xFFFF);
    test_sum += test_iunit_32_value(0xFFFFFF);
    test_sum += test_iunit_32_value(0xFFFFFFFF);
    test_sum += test_iunit_32_value(0x12345678);
    test_sum += test_iunit_32_value(0x4273BADC);
    return test_sum;
}

int main(void) {
    return test_iunit_16() + test_iunit_32();
}
