#include "huffman.h"
#include <stdio.h>
#include <stdlib.h>
#include "minheap/minheap.h"
#include "utility/huffman_serialization.h"

int _sort_item_comparator(const void *first, const void *second) {
    return (int) (*(const uint32_t *) first) - (long int) (*(const uint32_t *) second);
}

SortedItems *sort_by_frequency(const uint8_t *items, const uint32_t size) {
    SortedItems *sorted_items = malloc(sizeof(SortedItems));
    uint32_t *freq_of_position = calloc(sizeof(uint32_t), 0x100);

    if (freq_of_position != NULL && sorted_items != NULL) {
        register unsigned int unique_chars_count = 0U;

        for (register uint32_t i = 0U; i < size; ++i) {
            if (freq_of_position[items[i]]++ == 0) {
                ++unique_chars_count;
            }
        }

        SortItem *sort_items_array = calloc(sizeof(SortItem), unique_chars_count);
        if (sort_items_array != NULL) {
            register uint32_t i = 0U;
            for (register unsigned short j = 0U; j < 0x100; ++j) {
                if (freq_of_position[j] != 0) {
                    sort_items_array[i].value = (uint8_t) j;
                    sort_items_array[i].freq = freq_of_position[j];
                    ++i;
                }
            }
            qsort(sort_items_array, unique_chars_count, sizeof(SortItem), _sort_item_comparator);
            sorted_items->items = sort_items_array;
            sorted_items->size = (unsigned short) unique_chars_count;
        } else {
            printf("malloc error");
        }
    } else {
        printf("malloc error");
    }
    free(freq_of_position);
    return sorted_items;
}

HuffmanData *code_into_huffman_data(uint8_t *items, const uint32_t size) {
    if (size == 0) {
        printf("no items to code");
        return NULL;
    }
    return _code_huffman_string(items, size, sort_by_frequency(items, size));
}

HuffmanTree *build_huffman_tree(SortedItems *sorted_items) {
    if (sorted_items != NULL && sorted_items->size > 0) {
        minheap *min_heap = create_min_heap_minheap(sorted_items->size);
        HuffmanNode *nodes = (HuffmanNode *) calloc(sizeof(HuffmanNode), sorted_items->size);

        if (min_heap != NULL && nodes != NULL) {
            for (register uint32_t i = 0U; i < sorted_items->size; ++i) {
                nodes[i].freq = sorted_items->items[sorted_items->size - i - 1].freq;
                nodes[i].value = sorted_items->items[sorted_items->size - i - 1].value;
                insert_minheap(min_heap, create_heap_data_minheap(nodes[i].freq, &nodes[i]));
            }

            while (min_heap->size > 1) {
                HuffmanNode *left = (HuffmanNode *) extract_min(min_heap)->data;
                HuffmanNode *right = (HuffmanNode *) extract_min(min_heap)->data;
                HuffmanNode *parent = _create_parent_huffman_node(left, right);
                insert_minheap(min_heap, create_heap_data_minheap(parent->freq, parent));
            }
            HuffmanTree *tree = malloc(sizeof(HuffmanTree));
            if (tree != NULL) {
                tree->root = (HuffmanNode *) extract_min(min_heap)->data;
                tree->size = sorted_items->size;
                delete_minheap(min_heap);
                return tree;
            } else {
                printf("malloc error");
            }
        }
    }
    return NULL;
}

HuffmanNode *_create_parent_huffman_node(HuffmanNode *left_child, HuffmanNode *right_child) {
    HuffmanNode *parent_node = calloc(sizeof(HuffmanNode), 1);
    if (parent_node != NULL) {
        parent_node->left = left_child;
        parent_node->right = right_child;
        parent_node->left->parent = parent_node;
        parent_node->right->parent = parent_node;
        parent_node->freq = left_child->freq + right_child->freq;
    }
    return parent_node;
}

void _delete_huffman_nodes(HuffmanNode *node) {
    //TODO fixme
    //leaf is not there anymore ?! feeefeee
    if (node != NULL) {
        _delete_huffman_nodes(node->left);
        _delete_huffman_nodes(node->right);
        free(node);
        node = NULL;
    }
}

HuffmanData *_code_huffman_string(const uint8_t input[], const uint32_t input_size, SortedItems *sorted_items) {
    HuffmanData *data = malloc(sizeof(HuffmanData));
    HuffmanTree *tree = build_huffman_tree(sorted_items);
    HuffmanNode **leaves = (malloc(sizeof(HuffmanNode *) * 0x100));
    int *code_size = malloc(sizeof(int) * 0x100);
    if (leaves != NULL && code_size != NULL && tree != NULL && data != NULL) {
        _set_leaf_nodes(leaves, tree->root);
        const uint32_t bits_needed = _set_codes_size(leaves, code_size, sorted_items);

        free(code_size);
        code_size = NULL;

        uint8_t *output_buffer = calloc(1, _fill_bytes_for_bits(bits_needed));
        uint8_t **output = &output_buffer;

        if (output_buffer != NULL) {
            uint32_t bit_pos = 0U;

            for (register uint32_t i = 0U; i < input_size; ++i) {
                bit_pos += _add_huffman_code(output, leaves[input[i]], bit_pos, 0) - 1;
            }
            //_delete_huffman_tree(tree);
            free(leaves);
            leaves = NULL;

            data->bits = bits_needed;
            data->coded_array = *output;
            data->sort_items = sorted_items;
        } else {
            printf("malloc error");
        }
    } else {
        printf("malloc error");
        return NULL;
    }

    return data;
}

uint32_t _set_codes_size(HuffmanNode **leafs, int *code_size, SortedItems *sorted_items) {
    uint32_t bits = 0U;
    for (register int i = 0; i < sorted_items->size; ++i) {
        code_size[sorted_items->items[i].value] = _get_leaf_height(leafs[sorted_items->items[i].value]);
        bits += code_size[sorted_items->items[i].value] * sorted_items->items[i].freq;
    }
    return bits;
}

int _get_leaf_height(HuffmanNode *leaf) {
    if (leaf->parent != NULL) {
        return 1 + _get_leaf_height(leaf->parent);
    }
    return 0;
}

uint32_t _add_huffman_code(uint8_t **dest, HuffmanNode *leaf, const uint32_t bit_pos, uint32_t steps) {
    HuffmanNode *parent = leaf->parent;
    if (parent != NULL) {
        steps = _add_huffman_code(dest, parent, bit_pos, steps);
        _set_bit_at_pos(*dest, (bit_pos + steps) - 1, parent->right == leaf ? 1 : 0);
    }
    return steps + 1;
}

void _set_leaf_nodes(HuffmanNode **leafs, HuffmanNode *node) {
    //only need to check one side because parent has always two
    if (node->left == NULL) {
        leafs[node->value] = node;
    } else {
        _set_leaf_nodes(leafs, node->left);
        _set_leaf_nodes(leafs, node->right);
    }
}

void _set_bit_at_pos(uint8_t *dest, const uint32_t pos, const uint8_t value) {
    uint8_t write_value = value;
    write_value <<= 7 - (pos % 8);
    dest[pos / 8] |= write_value;
}

int decode_huffman_data(HuffmanData *hd, uint8_t **dest, uint32_t *out_size) {
    const uint32_t char_count = _get_amount_of_character(hd->sort_items);

    HuffmanTree *tree = build_huffman_tree(hd->sort_items);
    if (tree != NULL) {
        *dest = calloc(1, char_count);

        if (out_size != NULL) {
            *out_size = char_count;
        }

        //todo malloc error check
        if (*dest != NULL) {
            register uint32_t bit = 0U;
            register uint32_t dest_pos = 0U;

            while (dest_pos < char_count) {
                HuffmanNode *current_node = tree->root;
                while (current_node->left != NULL) {
                    const uint8_t read = hd->coded_array[bit / 8];
                    if (((read >> (7 - (bit % 8))) & 1) == 0) {
                        current_node = current_node->left;
                    } else {
                        current_node = current_node->right;
                    }
                    ++bit;
                }
                (*dest)[dest_pos++] = current_node->value;
            }
        } else {
            printf("dest malloc error\n");
        }
        //_delete_huffman_tree(tree);
    } else {
        printf("tree malloc error\n");
    }

    return 0;
}

void _delete_huffman_tree(HuffmanTree *tree) {
    _delete_huffman_nodes(tree->root);
    free(tree);
    tree = NULL;
}

uint32_t _get_items_sum(SortedItems *sort_items) {
    uint32_t sum = 0U;
    for (register uint32_t i = 0; i < sort_items->size; ++i) {
        sum += sort_items->items[i].freq;
    }
    return sum;
}

void delete_huffman_data(HuffmanData *data) {
    free(data->coded_array);
    data->coded_array = NULL;
    _delete_sorted_items(data->sort_items);
    free(data);
    data = NULL;
}

void _delete_sorted_items(SortedItems *sort_items) {
    free(sort_items);
    sort_items = NULL;
}

int _node_comparator(const void *first, const void *second) {
    return (long int) (*(const uint32_t *) first) - (long int) (*(const uint32_t *) second);
}

uint32_t _fill_bytes_for_bits(const uint32_t bits) {
    return (bits / 8U) + ((bits % 8U) ? 1U : 0U);
}

uint32_t _get_amount_of_character(SortedItems *sorted_items) {
    uint32_t amount = 0U;
    for (register int i = 0; i < sorted_items->size; ++i) {
        amount += sorted_items->items[i].freq;
    }
    return amount;
}

void huffman_code_file_to_file(FILE *src, FILE *des) {
    uint8_t *buffer = malloc(BUFFSIZE_FILE);
    if (buffer != NULL) {
        unsigned long read_offset = 0U;
        uint32_t elements_read;
        do {
            if (fseek(src, (long) read_offset, SEEK_SET) != 0) {
                printf("fseek error\n");
            } //trivial
            elements_read = fread(buffer, 1, BUFFSIZE_FILE, src);
            printf("write\n");
            HuffmanData *hd = code_into_huffman_data(buffer, elements_read);
            uint8_t *write_bytes = NULL;
            uint32_t to_write_bytes = 0U;
            serialize_huffman_data(hd, &write_bytes, &to_write_bytes);
            fwrite(write_bytes, 1, to_write_bytes, des);
            delete_huffman_data(hd);
            read_offset += elements_read;
        } while (elements_read == BUFFSIZE_FILE);
        printf("write done\n");
    }
}

void huffman_decode_file_to_file(FILE *src, FILE *des) {
    uint8_t *buffer = malloc(BUFFSIZE_FILE);
    if (buffer != NULL) {
        unsigned long read_offset = 0;
        uint32_t elements_read;
        uint32_t byte_needed_for_data = 0U;

        do {
            if (fseek(src, (long) read_offset, SEEK_SET) != 0) {
                printf("fseek erro\n");
            }
            elements_read = fread(buffer, 1, BUFFSIZE_FILE, src);
            printf("read\n");
            //TODO #3 last 3 chars are not getting deserialized
            HuffmanData *hd = deserialize_huffman_data(buffer, &byte_needed_for_data);
            uint8_t **decoded = malloc(sizeof(uint8_t **));
            if (decoded != NULL) {
                uint32_t output_size = 0U;
                decode_huffman_data(hd, decoded, &output_size);
                if (*decoded != NULL) {
                    fwrite(*decoded, 1, output_size, des);
                }
            }
            free(decoded);
            //delete_huffman_data(hd);
            //TODO #2 read offset not working corretly
            read_offset += byte_needed_for_data + 2;
        } while (elements_read > byte_needed_for_data);
        printf("read done\n");
    }
}


uint32_t _get_huffman_data_needed_bytes(HuffmanData *hd) {
    return _get_huffman_data_needed_bytes_add_coded_string(hd, _fill_bytes_for_bits(hd->bits));
}

uint32_t _get_huffman_data_needed_bytes_add_coded_string(HuffmanData *hd, const uint32_t coded_string_bytes) {
    //sort count + size of uint32_t + bits + sorteditems + coded_string size
    return 3 + sizeof(uint32_t) + sizeof(SortItem) * hd->sort_items->size + coded_string_bytes;
}