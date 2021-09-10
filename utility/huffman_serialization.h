#ifndef HUFFMAN_TEST_HUFFMAN_SERIALIZATION_H
#define HUFFMAN_TEST_HUFFMAN_SERIALIZATION_H

#include <stddef.h>
#include <stdint.h>
#include "../huffman.h"
#include "independent_int.h"

#define SORT_ITEM_SIZE_OF 2
#define BITS_SIZE_OF 4

typedef struct {
    iuint_64_t freq;
    unsigned char value;
} SerializeSortItem;

typedef struct {
    iuint_16_t sort_item_count;
    iuint_32_t bits;
    SerializeSortItem *sort_items; //size is sort_item_count
    unsigned char *code; //size is bits/8+Rest
} HuffmanSerializeData;

int serialize_huffman_data(HuffmanData *hd, unsigned char **dest, size_t *out_total_byte);

HuffmanData *deserialize_huffman_data(const unsigned char *src, size_t *out_byte_read);

HuffmanSerializeData *huffman_data_to_serialize_data(HuffmanData *hd);

int
deserialize_huffman_serialize_data(const unsigned char *src, HuffmanSerializeData **out_hsd, size_t *out_total_bytes);

HuffmanData *serialize_data_to_huffman_data(HuffmanSerializeData *hsd);

SortItem *serialize_sort_items_to_sort_item(SerializeSortItem *serialize_sort_item, size_t count);

SerializeSortItem *sort_items_to_serialize_sort_item(SortItem *sortItems, size_t count);

#endif //HUFFMAN_TEST_HUFFMAN_SERIALIZATION_H
