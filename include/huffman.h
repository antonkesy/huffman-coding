#ifndef HUFFMAN_HUFFMAN_H
#define HUFFMAN_HUFFMAN_H

#include <stdint.h>

typedef struct
{
    uint64_t freq;
    uint8_t value;
} SortItem;

typedef struct
{
    uint16_t size; //max 256
    SortItem *items;
} SortedItems;

typedef struct
{
    uint64_t length;
    uint8_t *coded_array;
    SortedItems *sort_items;
} HuffmanData;


//code uint8_t array into hd and reverse
HuffmanData *code_into_huffman_data(uint8_t *items, const uint32_t size);

int decode_huffman_data(HuffmanData *hd, uint8_t **dest, uint32_t *out_size);

SortedItems *sort_by_frequency(const uint8_t *items, const uint32_t size);

//delete
void delete_huffman_data(HuffmanData *data);

void delete_sorted_items(SortedItems *sort_items);

//files

void huffman_code_file_to_file(const char *src_file_name, const char *des_coded_file_name, long buffer_size);

void huffman_decode_file_to_file(const char *src_coded_file_name, const char *des_file_name);

#endif