#include <stdlib.h>
#include <stddef.h>
#include "independent_int.h"

void *fill_iuint_x(const void *in, const size_t size_of_iuint) {
    void *return_value = calloc(size_of_iuint, 1);
    if (return_value != NULL) {
        for (size_t i = 0U; i < size_of_iuint; ++i) {
#ifdef BIG_ENDIAN
            ((unsigned char *) return_value)[i] = ((unsigned char *) in)[size_of_iuint - i - 1];
#else
            ((unsigned char *) return_value)[i] = ((unsigned char *) in)[i];
#endif
        }
    }
    return return_value;
}

void *get_iunit_x_value(const void *iunit_in, const size_t size_of_iuint) {
    void *return_value = calloc(size_of_iuint, 1);
    if (return_value != NULL) {
        for (size_t i = 0U; i < size_of_iuint; ++i) {
#ifdef BIG_ENDIAN
            ((unsigned char *) return_value)[i] = ((unsigned char *) iunit_in)[size_iuint - i - 1];
#else
            ((unsigned char *) return_value)[i] = ((unsigned char *) iunit_in)[i];
#endif
        }
    }
    return return_value;
}

iuint_16_t *fill_iuint_16(const uint16_t *in) {
    return fill_iuint_x(in, sizeof(iuint_16_t));
}

uint16_t *get_iuint_16_value(const iuint_16_t *in) {
    return get_iunit_x_value(in, sizeof(iuint_16_t));
}

iuint_32_t *fill_iuint_32(const uint32_t *in) {
    return fill_iuint_x(in, sizeof(iuint_32_t));
}

uint32_t *get_iuint_32_value(const iuint_32_t *in) {
    return get_iunit_x_value(in, sizeof(iuint_32_t));
}

iuint_64_t *fill_iuint_64(const uint64_t *in) {
    return fill_iuint_x(in, sizeof(iuint_64_t));
}

uint64_t *get_iuint_64_value(const iuint_64_t *in) {
    return get_iunit_x_value(in, sizeof(iuint_64_t));
}