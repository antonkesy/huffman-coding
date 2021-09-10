#ifndef _HUFFMAN_UTILITY_H
#define _HUFFMAN_UTILITY_H

#include <stdbool.h>
#include "../huffman.h"
//print
void print_huffman_tree(HuffmanTree *tree);
void print_huffman_nodes(HuffmanNode *node);
void print_huffman_node(void *node);
void print_char_as_binary(unsigned char c);
void print_coded_string(HuffmanData *hd);

//compare
bool is_huffman_data_equal(HuffmanData *hd1, HuffmanData *hd2);
bool is_coded_string_equal(unsigned char *coded_string_1, unsigned char *coded_string_2, size_t size);
bool is_sorted_items_equal(SortedItems *items1, SortedItems *items2);
bool is_sort_item_equal(SortItem *item1, SortItem *item2);

#endif