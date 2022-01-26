#ifndef _HUFFMAN_UTILITY_H
#define _HUFFMAN_UTILITY_H

#include <stdbool.h>
#include <stdint.h>
#include "../huffman.h"
//print
void print_huffman_tree(HuffmanTree *tree);
void print_huffman_nodes(HuffmanNode *node);
void print_huffman_node(void *node);
void print_8bit_as_binary(uint8_t c);
void print_coded_string(HuffmanData *hd);

//compare
bool is_huffman_data_equal(HuffmanData *hd1, HuffmanData *hd2);
bool uint8_cmp(const uint8_t *string_1, const uint8_t *string_2, uint32_t size);
bool is_sorted_items_equal(SortedItems *items1, SortedItems *items2);
bool is_sort_item_equal(SortItem *item1, SortItem *item2);

#endif