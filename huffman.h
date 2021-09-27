#ifndef _HUFFMAN_H
#define _HUFFMAN_H

#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

struct Node
{
    uint32_t freq;
    uint8_t value;
    struct Node *left, *right, *parent;
};

typedef struct Node HuffmanNode;

typedef struct
{
    uint32_t size;
    HuffmanNode *root;
} HuffmanTree;

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
    uint32_t bits;
    uint8_t *coded_array;
    SortedItems *sort_items;
} HuffmanData;


//TODO return value is int and output is parameter

//code uint8_t array into hd and reverse
HuffmanData *code_into_huffman_data(uint8_t *items, const uint32_t size);

int decode_huffman_data(HuffmanData *hd, uint8_t **dest, uint32_t *out_size);

SortedItems *sort_by_frequency(const uint8_t *items, const uint32_t size);

HuffmanData *_code_huffman_string(const uint8_t input[], const uint32_t input_size, SortedItems *sorted_items);

//tree
HuffmanTree *build_huffman_tree(SortedItems *sorted_items);

HuffmanNode *_create_parent_huffman_node(HuffmanNode *left_child, HuffmanNode *right_child);

//coding
int _get_leaf_height(HuffmanNode *leaf);

void _set_leaf_nodes(HuffmanNode **leaves, HuffmanNode *node);

uint32_t _set_codes_size(HuffmanNode **leaves, int *code_size, SortedItems *sorted_items);

uint32_t _add_huffman_code(uint8_t **dest, HuffmanNode *leaf, const uint32_t bit_pos, uint32_t steps);


//utility
int _sort_item_comparator(const void *first, const void *second);

int _node_comparator(const void *first, const void *second);

void _set_bit_at_pos(uint8_t *dest, const uint32_t pos, const uint8_t value);

uint32_t _get_items_sum(SortedItems *sort_items);

uint32_t _fill_bytes_for_bits(const uint32_t bits);

uint32_t _get_amount_of_character(SortedItems *sorted_items);

//delete
void delete_huffman_data(HuffmanData *data);

void _delete_huffman_nodes(HuffmanNode *node);

void _delete_huffman_tree(HuffmanTree *tree);

void _delete_sorted_items(SortedItems *sort_items);

#endif