#ifndef HUFFMAN_TEST_INDEPENDENT_INT_H
#define HUFFMAN_TEST_INDEPENDENT_INT_H

#include <stdint.h>
#include <stddef.h>

#if 43981 == 0xABCD
#define LITTLE_ENDIAN
#else
#define BIG_ENDIAN
#endif

typedef struct {
    unsigned char bytes[2];
} iuint_16_t;

typedef struct {
    unsigned char bytes[4];
} iuint_32_t;

typedef struct {
    unsigned char bytes[8];
} iuint_64_t;

void *fill_iuint_x(const void *in, const size_t size_of_iuint);

iuint_16_t *fill_iuint_16(const uint16_t *in);

uint16_t *get_iuint_16_value(const iuint_16_t *in);

iuint_32_t *fill_iuint_32(const uint32_t *in);

uint32_t *get_iuint_32_value(const iuint_32_t *in);

iuint_64_t *fill_iuint_64(const uint64_t *in);

uint64_t *get_iuint_64_value(const iuint_64_t *in);

#endif //HUFFMAN_TEST_INDEPENDENT_INT_H
