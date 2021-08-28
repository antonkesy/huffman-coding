#ifndef _HUFFMAN_UTILITY_H
#define _HUFFMAN_UTILITY_H

#include "huffman.h"
//print
void print_huffman_tree(HuffmanTree *tree);
void print_huffman_nodes(HuffmanNode *node);
void print_huffman_node(void *node);
void print_char_as_binary(unsigned char c);
void print_coded_string(HuffmanData *hd);

//compare
int is_huffman_data_equal(HuffmanData *hd1, HuffmanData *hd2);

#endif