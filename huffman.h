#ifndef _HUFFMAN_H
#define _HUFFMAN_H

#ifndef _STDDEF_H
#include <stddef.h>
#endif
#ifndef _STDBOOL_H
#include <stdbool.h>
#endif

struct Node
{
    size_t freq;
    char value;
    struct Node *left, *right, *parent;
};

typedef struct Node HuffmanNode;

typedef struct
{
    size_t size;
    HuffmanNode *root;
} HuffmanTree;

typedef struct
{
    size_t freq;
    char value;
} SortItem;

typedef struct
{
    size_t size;
    SortItem *items;
} SortedItems;

typedef struct
{
    size_t bits;
    unsigned char *codedString;
    SortedItems *items;
} HuffmanData;

//TODO return value is int and output is parameter

//
HuffmanData *code_into_huffmanData(char *items, size_t size);
int decode_huffman_data(HuffmanData *hd, char **dest, size_t *out_size);

SortedItems *sort_by_frequency(char *items, size_t size);
HuffmanData *_code_huffman_string(char input[], size_t inputSize, SortedItems *sortedItems);

//tree
HuffmanTree *build_huffman_tree(SortedItems *sortedItems);
HuffmanNode *_create_value_huffman_node(SortItem *sortItem);
HuffmanNode *_create_parent_huffman_node(HuffmanNode *leftChild, HuffmanNode *rightChild);

//coding
int _get_leaf_height(HuffmanNode *leaf);
void _set_leaf_nodes(HuffmanNode **leafs, HuffmanNode *node);
size_t _set_codes_size(HuffmanNode **leafs, int *codeSize, SortedItems *sortedItems);
size_t _add_huffman_code(char **output, HuffmanNode *leaf, size_t bitPos, size_t steps);

//utility
int _sort_item_comparator(const void *first, const void *second);
int _node_comparator(const void *first, const void *second);
void _set_bit_at_pos(char *dest, size_t pos, char value);
size_t _get_items_sum(SortedItems *items);
size_t _fill_bytes_for_bits(size_t bits);
size_t _get_amount_of_character(SortedItems *sortedItems);

//delete
void deleteHuffmanData(HuffmanData *data);
void _delte_huffman_nodes(HuffmanNode *root);
void _delete_huffman_tree(HuffmanTree *heap);
void _delete_sorted_items(SortedItems *items);

//print
void print_huffman_tree(HuffmanTree *heap);
void print_huffman_nodes(HuffmanNode *node);
void print_huffman_node(void *node);
void print_char_as_binary(char c);
void print_coded_string(HuffmanData *hd);
#endif