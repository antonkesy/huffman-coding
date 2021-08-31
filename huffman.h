#ifndef _HUFFMAN_H
#define _HUFFMAN_H

#ifndef _STDDEF_H
#include <stddef.h>
#endif
#ifndef _STDBOOL_H
#include <stdbool.h>
#endif
#ifndef _STDIO_H
#include <stdio.h>
#endif

#define BUFFSIZE_FILE 16384

struct Node
{
   size_t freq;
   unsigned char value;
   struct Node* left, * right, * parent;
};

typedef struct Node HuffmanNode;

typedef struct
{
   size_t size;
   HuffmanNode* root;
} HuffmanTree;

typedef struct
{
   size_t freq;
   unsigned char value;
} SortItem;

typedef struct
{
   unsigned short size; //max 256
   SortItem* items;
} SortedItems;

typedef struct
{
   size_t bits;
   unsigned char* coded_array;
   SortedItems* sort_items;
} HuffmanData;

//TODO return value is int and output is parameter

//code unsigned char array into hd and reverse
HuffmanData* code_into_huffman_data(unsigned char* items, const size_t size);
int decode_huffman_data(HuffmanData* hd, unsigned char** dest, size_t* out_size);

//code file into new file
void huffman_code_file_to_file(FILE* src, FILE* des);
void huffman_decode_file_to_file(FILE* src, FILE* des);

SortedItems* sort_by_frequency(const unsigned char* items, const size_t size);
HuffmanData* _code_huffman_string(const unsigned char input[], const size_t input_size, SortedItems* sorted_items);

//tree
HuffmanTree* build_huffman_tree(SortedItems* sorted_items);
HuffmanNode* _create_parent_huffman_node(HuffmanNode* left_child, HuffmanNode* right_child);

//coding
int _get_leaf_height(HuffmanNode* leaf);
void _set_leaf_nodes(HuffmanNode** leafs, HuffmanNode* node);
size_t _set_codes_size(HuffmanNode** leafs, int* code_size, SortedItems* sorted_items);
size_t _add_huffman_code(unsigned char** dest, HuffmanNode* leaf, const size_t bit_pos, size_t steps);
size_t serialize_huffman_data(HuffmanData* hd, unsigned char** dest);
HuffmanData* deserialize_huffman_data(const unsigned char* src, size_t* out_byte_read);

//utility
long int _sort_item_comparator(const void* first, const void* second);
long int _node_comparator(const void* first, const void* second);
void _set_bit_at_pos(unsigned char* dest, const size_t pos, const unsigned char value);
size_t _get_items_sum(SortedItems* sort_items);
size_t _fill_bytes_for_bits(const size_t bits);
size_t _get_amount_of_character(SortedItems* sorted_items);
size_t _get_huffman_data_needed_bytes(HuffmanData* hd);
size_t _get_huffman_data_needed_bytes_add_coded_string(HuffmanData* hd, const size_t coded_string_bytes);

//delete
void delete_huffman_data(HuffmanData* data);
void _delete_huffman_nodes(HuffmanNode* node);
void _delete_huffman_tree(HuffmanTree* tree);
void _delete_sorted_items(SortedItems* sort_items);
#endif