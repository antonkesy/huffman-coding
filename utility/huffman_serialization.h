#ifndef HUFFMAN_TEST_HUFFMAN_SERIALIZATION_H
#define HUFFMAN_TEST_HUFFMAN_SERIALIZATION_H

#include <stddef.h>
#include <stdint.h>
#include "../huffman.h"
#include "independent_int.h"

typedef struct
{
    iuint_64_t freq;
    uint8_t value;
} SerializeSortItem;

typedef struct
{
    iuint_16_t sort_item_count;
    iuint_64_t length;
    SerializeSortItem *sort_items; //size is sort_item_count
    uint8_t *code; //length =  (bits/8+Rest)
} HuffmanSerializeData;

int serialize_huffman_data(HuffmanData *hd, uint8_t **dest, uint32_t *out_total_byte);

HuffmanData *deserialize_huffman_data(const uint8_t *src, uint32_t *out_byte_read);

HuffmanSerializeData *huffman_data_to_serialize_data(HuffmanData *hd);

int deserialize_huffman_serialize_data(const uint8_t *src, HuffmanSerializeData **out_hsd, uint32_t *out_total_bytes);

HuffmanData *serialize_data_to_huffman_data(HuffmanSerializeData *hsd);

SortItem *serialize_sort_items_to_sort_item(SerializeSortItem *serialize_sort_item, uint32_t count);

SerializeSortItem *sort_items_to_serialize_sort_item(SortItem *sortItems, uint32_t count);

size_t get_huffman_serialize_data_size(const uint16_t sort_item_count, const uint32_t size_coded_string);

void _delete_serialize_data(HuffmanSerializeData *hsd);

#endif //HUFFMAN_TEST_HUFFMAN_SERIALIZATION_H
