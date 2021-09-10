#ifndef HUFFMAN_TEST_HUFFMAN_SERIALIZATION_H
#define HUFFMAN_TEST_HUFFMAN_SERIALIZATION_H

#include <stddef.h>
#include <stdint.h>
#include "../huffman.h"
#include "independent_int.h"


typedef struct {
    iuint_16_t sort_item_count;
    iuint_32_t bits;
    SortItem *sort_items; //size is sort_item_count
    unsigned char *code; //size is bits/8+Rest
} HuffmanSerializeData;

int serialize_huffman_data(HuffmanData *hd, unsigned char **dest, size_t *out_total_byte);

HuffmanData *deserialize_huffman_data(const unsigned char *src, size_t *out_byte_read);

HuffmanSerializeData *huffman_data_to_serialize_data(HuffmanData *hd);

HuffmanData *serialize_data_to_huffman_data(HuffmanSerializeData *hsd);


#endif //HUFFMAN_TEST_HUFFMAN_SERIALIZATION_H
