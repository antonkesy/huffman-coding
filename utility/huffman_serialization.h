#ifndef HUFFMAN_TEST_HUFFMAN_SERIALIZATION_H
#define HUFFMAN_TEST_HUFFMAN_SERIALIZATION_H

#include <stddef.h>
#include "../huffman.h"

typedef struct {

} HuffmanSerializeData;

size_t serialize_huffman_data(HuffmanData *hd, unsigned char **dest);

HuffmanData *deserialize_huffman_data(const unsigned char *src, size_t *out_byte_read);

#endif //HUFFMAN_TEST_HUFFMAN_SERIALIZATION_H
