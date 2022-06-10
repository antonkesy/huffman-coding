#ifndef HUFFMAN_HUFFMAN_HPP
#define HUFFMAN_HUFFMAN_HPP

#include "../include/huffman_coding.hpp"

namespace huffman_coding {
    class HuffmanCoder {
    public:
        explicit HuffmanCoder(const std::vector<unsigned char> &input);

        std::unique_ptr<IHuffmanData> get();
    };
}

/*
struct Node {
    uint32_t freq;
    uint8_t value;
    struct Node *left, *right, *parent;
};

typedef struct Node HuffmanNode;

typedef struct {
    uint64_t size;
    HuffmanNode *root;
} HuffmanTree;

IHuffmanData *code_huffman_string(const uint8_t input[], const uint32_t input_size, ISortedChars *sorted_chars);

//tree
HuffmanTree *build_huffman_tree(ISortedChars *sorted_chars);

HuffmanNode *create_parent_huffman_node(HuffmanNode *left_child, HuffmanNode *right_child);

//coding
int get_leaf_height(HuffmanNode *leaf);

void set_leaf_nodes(HuffmanNode **leaves, HuffmanNode *node);

MemorySpace set_codes_size(HuffmanNode **leaves, int *code_size, ISortedChars *sorted_chars);

uint32_t add_huffman_code(uint8_t **dest, HuffmanNode *leaf, const uint32_t bit_pos, uint32_t steps);


//utility
int sort_item_comparator(const void *first, const void *second);

void set_bit_at_pos(uint8_t *dest, const uint32_t pos, const uint8_t value);

uint32_t get_amount_of_character(ISortedChars *sorted_chars);

//delete

void delete_huffman_nodes(HuffmanNode *node);

void delete_huffman_tree(HuffmanTree *tree);

 */
#endif