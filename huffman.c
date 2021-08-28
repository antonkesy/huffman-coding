#include "huffman.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "minheap/minheap.h"

int _sort_item_comparator(const void *first, const void *second)
{
    return (*(size_t *)first) - (*(size_t *)second);
}

SortedItems *sort_by_frequency(unsigned char *items, size_t size)
{
    SortedItems *sortedItems = malloc(sizeof(SortedItems));
    size_t *freqOfPosition = calloc(sizeof(size_t), 0x100);
    register size_t uniqueCharsCount = 0U;

    if (freqOfPosition != NULL)
    {
        for (register size_t i = 0U; i < size; ++i)
        {
            if (freqOfPosition[items[i]]++ == 0)
            {
                ++uniqueCharsCount;
            }
        }

        SortItem *sortItemsArray = calloc(sizeof(SortItem), uniqueCharsCount);
        if (sortItemsArray != NULL)
        {
            register size_t i = 0U;
            for (register size_t j = 0U; j < 0x100; ++j)
            {
                if (freqOfPosition[j] != 0)
                {
                    sortItemsArray[i].value = j;
                    sortItemsArray[i].freq = freqOfPosition[j];
                    ++i;
                }
            }
        }
        else
        {
            printf("malloc error");
        }

        qsort(sortItemsArray, uniqueCharsCount, sizeof(SortItem), _sort_item_comparator);

        sortedItems->items = sortItemsArray;
        sortedItems->size = uniqueCharsCount;
    }
    else
    {
        //MALLOC ERROR
        printf("malloc error");
    }
    free(freqOfPosition);
    freqOfPosition = NULL;

    return sortedItems;
}

HuffmanData *code_into_huffmanData(unsigned char *items, size_t size)
{
    return _code_huffman_string(items, size, sort_by_frequency(items, size));
}

HuffmanTree *build_huffman_tree(SortedItems *sortedItems)
{
    minheap *minheap = create_min_heap_minheap(sortedItems->size);
    HuffmanNode *nodes = (HuffmanNode *)calloc(sizeof(HuffmanNode), sortedItems->size);

    for (register size_t i = 0U; i < sortedItems->size; ++i)
    {
        nodes[i].freq = sortedItems->items[sortedItems->size - i - 1].freq;
        nodes[i].value = sortedItems->items[sortedItems->size - i - 1].value;
        insert_minheap(minheap, create_heap_data_minheap(nodes[i].freq, &nodes[i]));
    }

    while (minheap->size > 1)
    {
        HuffmanNode *left = (HuffmanNode *)extract_min(minheap)->data;
        HuffmanNode *right = (HuffmanNode *)extract_min(minheap)->data;
        HuffmanNode *parent = _create_parent_huffman_node(left, right);
        insert_minheap(minheap, create_heap_data_minheap(parent->freq, parent));
    }
    HuffmanTree *tree = malloc(sizeof(HuffmanTree));
    if (tree != NULL)
    {
        tree->root = (HuffmanNode *)extract_min(minheap)->data;
        tree->size = sortedItems->size;
    }
    else
    {
        printf("malloc error");
    }

    delete_minheap(minheap);
    return tree;
}

void print_huffman_tree(HuffmanTree *tree)
{
    printf("Print tree:\n");
    if (tree->root == NULL)
    {
        printf("tree empty!\n");
    }
    else
    {
        print_huffman_nodes(tree->root);
    }
}

void print_huffman_nodes(HuffmanNode *node)
{
    if (node != NULL)
    {
        printf("node -> ");
        if (node->left != NULL && node->right != NULL)
        {
            printf("parent node sum = %u\n", node->freq);
            //parent node (should always have 2 children)
            printf("parent node %u left = ", node->freq);
            print_huffman_nodes(node->left);
            printf("parent node %u right = ", node->freq);
            print_huffman_nodes(node->right);
        }
        else
        {
            //value node
            printf("value node %c %u\n", node->value, node->freq);
        }
    }
}

HuffmanNode *_create_parent_huffman_node(HuffmanNode *leftChild, HuffmanNode *rightChild)
{
    //TODO check malloc error!
    HuffmanNode *parentNode = calloc(sizeof(HuffmanNode), 1);
    parentNode->left = leftChild;
    parentNode->right = rightChild;
    parentNode->left->parent = parentNode;
    parentNode->right->parent = parentNode;
    parentNode->freq = leftChild->freq + rightChild->freq;

    return parentNode;
}

void _delte_huffman_nodes(HuffmanNode *node)
{
    //TODO fixme
    //leaf is not there anymore ?! feeefeee
    if (node != NULL)
    {
        _delte_huffman_nodes(node->left);
        _delte_huffman_nodes(node->right);
        free(node);
        node = NULL;
    }
}

HuffmanData *_code_huffman_string(unsigned char input[], size_t inputSize, SortedItems *sortedItems)
{
    HuffmanTree *tree = build_huffman_tree(sortedItems);
    HuffmanData *data = malloc(sizeof(HuffmanData));
    HuffmanNode **leafs = (malloc(sizeof(HuffmanNode *) * 0x100));
    int *codeSize = malloc(sizeof(int) * 0x100);
    if (leafs != NULL && codeSize != NULL)
    {
        _set_leaf_nodes(leafs, tree->root);
        size_t bitsNeeded = _set_codes_size(leafs, codeSize, sortedItems);

        free(codeSize);
        codeSize = NULL;

        unsigned char *outputBuffer = calloc(1, _fill_bytes_for_bits(bitsNeeded));
        unsigned char **output = &outputBuffer;

        if (tree != NULL && data != NULL)
        {
            size_t bitPos = 0U;

            for (register size_t i = 0U; i < inputSize; ++i)
            {
                bitPos += _add_huffman_code(output, leafs[input[i]], bitPos, 0) - 1;
            }

            //_delete_huffman_tree(tree);
            free(leafs);
            leafs = NULL;

            data->bits = bitsNeeded;
            data->codedArray = *output;
            data->sort_items = sortedItems;
        }
        else
        {
            printf("malloc error");
        }
    }
    else
    {
        printf("malloc error");
    }

    return data;
}

size_t _set_codes_size(HuffmanNode **leafs, int *codeSize, SortedItems *sortedItems)
{
    size_t bits = 0U;
    for (register int i = 0; i < sortedItems->size; ++i)
    {
        codeSize[sortedItems->items[i].value] = _get_leaf_height(leafs[sortedItems->items[i].value]);
        bits += codeSize[sortedItems->items[i].value] * sortedItems->items[i].freq;
    }
    return bits;
}

int _get_leaf_height(HuffmanNode *leaf)
{
    if (leaf->parent != NULL)
    {
        return 1 + _get_leaf_height(leaf->parent);
    }
    else
    {
        return 0;
    }
}

size_t _add_huffman_code(unsigned char **output, HuffmanNode *leaf, size_t bitPos, size_t steps)
{
    HuffmanNode *parent = leaf->parent;
    if (parent != NULL)
    {
        steps = _add_huffman_code(output, parent, bitPos, steps);
        _set_bit_at_pos(*output, (bitPos + steps) - 1, parent->right == leaf ? 1 : 0);
    }
    return steps + 1;
}

void _set_leaf_nodes(HuffmanNode **leafs, HuffmanNode *node)
{
    //only need to check one side because parent has always two
    if (node->left == NULL)
    {
        leafs[node->value] = node;
    }
    else
    {
        _set_leaf_nodes(leafs, node->left);
        _set_leaf_nodes(leafs, node->right);
    }
}

void _set_bit_at_pos(unsigned char *dest, size_t pos, unsigned char value)
{
    unsigned char writeValue = value;
    writeValue <<= 7 - (pos % 8);
    dest[pos / 8] |= writeValue;
}

void print_char_as_binary(unsigned char c)
{

    size_t flag = 0x80;
    for (register char i = 0; i < 8; ++i)
    {
        printf("%c", (flag & c) == flag ? '1' : '0');
        if (((i + 1) % 4) == 0 && i != 31)
        {
            printf("_");
        }
        flag >>= 1;
    }
}

void print_coded_string(HuffmanData *hd)
{
    for (register size_t i = 0; i < _fill_bytes_for_bits(hd->bits); ++i)
    {
        print_char_as_binary(hd->codedArray[i]);
        printf(" ");
    }
}

int decode_huffman_data(HuffmanData *hd, unsigned char **dest, size_t *out_size)
{
    size_t charCount = _get_amount_of_character(hd->sort_items);

    HuffmanTree *tree = build_huffman_tree(hd->sort_items);
    if (tree != NULL)
    {
        *dest = calloc(1, charCount);

        if (out_size != NULL)
        {
            *out_size = charCount;
        }

        //todo malloc error check
        if (*dest != NULL)
        {
            register size_t bit = 0U;
            register size_t destPos = 0U;

            while (destPos < charCount)
            {
                HuffmanNode *currentNode = tree->root;
                while (currentNode->left != NULL)
                {
                    unsigned char read = hd->codedArray[bit / 8];
                    if (((read >> (7 - (bit % 8))) & 1) == 0)
                    {
                        currentNode = currentNode->left;
                    }
                    else
                    {
                        currentNode = currentNode->right;
                    }
                    ++bit;
                }
                (*dest)[destPos++] = currentNode->value;
            }
        }
        else
        {
            printf("dest malloc error\n");
        }
        //_delete_huffman_tree(tree);
    }
    else
    {
        printf("tree malloc error\n");
    }

    return 0;
}

void _delete_huffman_tree(HuffmanTree *tree)
{
    _delte_huffman_nodes(tree->root);
    free(tree);
    tree = NULL;
}

size_t _get_items_sum(SortedItems *sort_items)
{
    size_t sum = 0U;
    for (register size_t i = 0; i < sort_items->size; ++i)
    {
        sum += sort_items->items[i].freq;
    }
    return sum;
}

void delete_huffman_data(HuffmanData *data)
{
    free(data->codedArray);
    data->codedArray = NULL;
    _delete_sorted_items(data->sort_items);
    free(data);
    data = NULL;
}

void _delete_sorted_items(SortedItems *sort_items)
{
    free(sort_items);
    sort_items = NULL;
}

int _node_comparator(const void *first, const void *second)
{
    return (*(size_t *)first) - (*(size_t *)second);
}

void print_huffman_node(void *node)
{
    HuffmanNode *hNode = (HuffmanNode *)node;
    if (hNode->left == NULL && hNode->right == NULL)
    {
        printf("Value Node = %i %c\n", hNode->freq, hNode->value);
    }
    else
    {
        printf("Parent node = %i\n", hNode->freq);
    }
}

size_t _fill_bytes_for_bits(size_t bits)
{
    return (bits / 8U) + ((bits % 8U) ? 1U : 0U);
}

size_t _get_amount_of_character(SortedItems *sortedItems)
{
    size_t amount = 0U;
    for (register int i = 0; i < sortedItems->size; ++i)
    {
        amount += sortedItems->items[i].freq;
    }
    return amount;
}
void huffman_code_file_to_file(FILE *src, FILE *des)
{
    unsigned char buffer[BUFFSIZE_FILE];
    int elements_read = 0;

    do
    {
        elements_read = fread(buffer, 1, BUFFSIZE_FILE, src);
        printf("write\n");
        HuffmanData *hd = code_into_huffmanData(buffer, elements_read);
        unsigned char *write_bytes = NULL;
        size_t to_write_bytes = serialize_huffmandata(hd, &write_bytes);
        fwrite(write_bytes, 1, to_write_bytes, des);
        delete_huffman_data(hd);
    } while (elements_read == BUFFSIZE_FILE);
    printf("write done\n");
}
void huffman_decode_file_to_file(FILE *src, FILE *des)
{
    unsigned char buffer[BUFFSIZE_FILE];
    size_t read_offset = 0;
    size_t elements_read = 0;
    size_t byte_needed_for_data = 0U;

    do
    {
        if (fseek(src, read_offset, SEEK_SET) != 0)
        {
            printf("fseek erro\n");
        }
        elements_read = fread(buffer, 1, BUFFSIZE_FILE, src);
        if (elements_read > 0)
        {
            printf("read\n");
            HuffmanData *hd = deserialize_huffmandata(buffer, &byte_needed_for_data);
            unsigned char **decoded = malloc(sizeof(unsigned char **));
            size_t outputSize = 0U;
            decode_huffman_data(hd, decoded, &outputSize);
            fwrite(*decoded, 1, outputSize, des);
            free(decoded);
            //delete_huffman_data(hd);
            //TODO read offset not working corretly
            read_offset += byte_needed_for_data + 2;
        }
    } while (elements_read > 0);
    printf("read done\n");
}

size_t serialize_huffmandata(HuffmanData *huffmandata, unsigned char **dest)
{
    //first byte = sortItems count
    // sizeof(size_t) = bits of code
    // bytes 1 to sizeof(SortItem) * count = filled with sortItmes
    //rest is code
    size_t bytes_for_coded_string = _fill_bytes_for_bits(huffmandata->bits);
    size_t total_bytes = _get_huffmandata_needed_bytes_add_coded_string(huffmandata, bytes_for_coded_string);
    unsigned char *output = malloc(total_bytes);
    if (output != NULL)
    {
        output[0] = huffmandata->sort_items->size;
        output[1] = sizeof(size_t);
        int offset = 2;

        //bits
        for (int i = 0; i < sizeof(size_t); ++i)
        {
            output[i + offset] = ((unsigned char *)(&huffmandata->bits))[i];
        }
        offset += sizeof(size_t);

        //sort sort_items
        for (int i = 0; i <= huffmandata->sort_items->size * sizeof(SortItem); ++i)
        {
            output[i + offset] = ((unsigned char *)huffmandata->sort_items->items)[i];
        }
        offset += huffmandata->sort_items->size * sizeof(SortItem);

        //coded string
        for (int i = 0; i < bytes_for_coded_string; ++i)
        {
            output[i + offset] = huffmandata->codedArray[i];
        }

        *dest = output;
        return total_bytes;
    }
    return 0;
}

HuffmanData *deserialize_huffmandata(unsigned char *src, size_t *out_byte_read)
{
    HuffmanData *retData = NULL;
    HuffmanData *hd = malloc(sizeof(HuffmanData));
    if (hd != NULL && src != NULL)
    {
        unsigned char items_count = src[0];
        unsigned char size_of_size_t = src[1];
        if (size_of_size_t > sizeof(size_t))
        {
            printf("size_t is too small!\n");
        }
        SortItem *items = calloc(1, sizeof(SortItem) * items_count);
        SortedItems *sortedItems = malloc(sizeof(SortedItems));
        if (items != NULL && sortedItems != NULL)
        {

            int offset = 2;
            sortedItems->size = items_count;
            sortedItems->items = items;
            hd->sort_items = sortedItems;

            for (int i = 0; i < size_of_size_t; ++i)
            {
                ((unsigned char *)(&hd->bits))[i] = src[i + offset];
            }
            offset += size_of_size_t;

            for (int i = 0; i <= items_count * sizeof(SortItem); ++i)
            {
                ((unsigned char *)hd->sort_items->items)[i] = src[i + offset];
            }
            offset += items_count * sizeof(SortItem);

            size_t coded_array_size = _fill_bytes_for_bits(hd->bits);
            //printf("!! %i\n", coded_array_size);
            //normal run stops here?!
            unsigned char *coded_array = malloc(coded_array_size);
            if (coded_array != NULL)
            {
                hd->codedArray = coded_array;
                for (size_t i = 0U; i < coded_array_size; ++i)
                {
                    hd->codedArray[i] = src[i + offset];
                }
                *out_byte_read = offset + coded_array_size;
                retData = hd;
            }
        }
    }
    return retData;
}

size_t _get_huffmandata_needed_bytes(HuffmanData *hd)
{
    return _get_huffmandata_needed_bytes_add_coded_string(hd, _fill_bytes_for_bits(hd->bits));
}

size_t _get_huffmandata_needed_bytes_add_coded_string(HuffmanData *hd, size_t coded_string_bytes)
{
    //sort count + size of size_t + bits + sorteditems + coded_string size
    return 2 + sizeof(size_t) + sizeof(SortItem) * hd->sort_items->size + coded_string_bytes;
}