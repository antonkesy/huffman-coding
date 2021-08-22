#include "huffman.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "priorityqueue/priorityqueue.h"

//TODO free memory

int _sort_item_comparator(const void *first, const void *second)
{
    return (*(size_t *)first) - (*(size_t *)second);
}

SortedItems *sort_by_frequency(char *items, size_t size)
{
    SortedItems *sortedItems = malloc(sizeof(SortedItems));
    size_t *freqOfPosition = calloc(0xFF, sizeof(size_t));
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

        SortItem *sortItemsArray = malloc(sizeof(SortItem) * uniqueCharsCount);
        if (sortItemsArray != NULL)
        {
            register size_t i = 0U;
            for (register size_t j = 0U; j < 0xFF; ++j)
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
    //free(freqOfPosition);

    return sortedItems;
}

HuffmanData *code_into_huffmanData(char *items, size_t size)
{
    //error check
    return _code_huffman_string(items, size, sort_by_frequency(items, size));
}

HuffmanTree *build_huffman_tree(SortedItems *sortedItems)
{
    HuffmanNode *root = NULL;
    priorityque *prioQ = createPQ(_node_comparator);
    HuffmanNode *nodes = (HuffmanNode *)calloc(sizeof(HuffmanNode), sortedItems->size);

    for (register size_t i = 0U; i < sortedItems->size; ++i)
    {
        nodes[i].freq = sortedItems->items[sortedItems->size - i - 1].freq;
        nodes[i].value = sortedItems->items[sortedItems->size - i - 1].value;
        push(prioQ, &nodes[i]);
    }

    while (prioQ->size > 1)
    {
        HuffmanNode *left = pop(prioQ);
        HuffmanNode *right = pop(prioQ);
        HuffmanNode *parent = _create_parent_huffman_node(left, right);
        push(prioQ, parent);
    }
    HuffmanTree *heap = malloc(sizeof(HuffmanTree));
    heap->root = pop(prioQ);
    heap->size = sortedItems->size;

    //TODO freeing crashes
    //free(prioQ);
    return heap;
}

void print_huffman_tree(HuffmanTree *heap)
{
    printf("Print heap:\n");
    if (heap->root == NULL)
    {
        printf("Heap empty!\n");
    }
    else
    {
        print_huffman_nodes(heap->root);
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

HuffmanNode *_create_value_huffman_node(SortItem *sortItem)
{
    //TODO check malloc error!
    HuffmanNode *newNode = calloc(sizeof(HuffmanNode), 1);
    newNode->value = sortItem->value;
    newNode->freq = sortItem->freq;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
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
    if (node != NULL)
    {
        if (node->left != NULL)
        {
            _delte_huffman_nodes(node->left);
        }
        if (node->right != NULL)
        {
            _delte_huffman_nodes(node->right);
        }
        free(node);
    }
}

HuffmanData *_code_huffman_string(char input[], size_t inputSize, SortedItems *sortedItems)
{
    HuffmanTree *tree = build_huffman_tree(sortedItems);
    HuffmanData *data = malloc(sizeof(HuffmanData));

    HuffmanNode **leafs = malloc(sizeof(HuffmanNode *) * 0x100);
    int *codeSize = malloc(sizeof(int) * 0x100);
    if (leafs != NULL && codeSize != NULL)
    {
        _set_leaf_nodes(leafs, tree->root);
        size_t bitsNeeded = _set_codes_size(leafs, codeSize, sortedItems);

        char *outputBuffer = calloc(1, _fill_bytes_for_bits(bitsNeeded));
        char **output = &outputBuffer;

        if (tree != NULL && data != NULL)
        {
            size_t bitPos = 0U;

            for (register size_t i = 0U; i < inputSize; ++i)
            {
                bitPos += _add_huffman_code(output, leafs[input[i]], bitPos, 0) - 1;
            }
            data->bits = bitsNeeded;
            data->codedString = *output;
            data->items = sortedItems;
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

size_t _add_huffman_code(char **output, HuffmanNode *leaf, size_t bitPos, size_t steps)
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

void _set_bit_at_pos(char *dest, size_t pos, char value)
{
    char writeValue = value;
    writeValue <<= 7 - (pos % 8);
    dest[pos / 8] |= writeValue;
}

void print_char_as_binary(char c)
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
        print_char_as_binary(hd->codedString[i]);
        printf(" ");
    }
}

int decode_huffman_data(HuffmanData *hd, char **dest, size_t *out_size)
{
    HuffmanTree *tree = build_huffman_tree(hd->items);

    HuffmanNode **leafs = malloc(sizeof(HuffmanNode *) * 0x100);

    size_t charCount = _get_amount_of_character(hd->items);

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
                char read = hd->codedString[bit / 8];
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

    return 0;
}

void _delete_huffman_tree(HuffmanTree *heap)
{
    _delte_huffman_nodes(heap->root);
    free(heap);
}

size_t _get_items_sum(SortedItems *items)
{
    size_t sum = 0U;
    for (register size_t i = 0; i < items->size; ++i)
    {
        sum += items->items[i].freq;
    }
    return sum;
}

void deleteHuffmanData(HuffmanData *data)
{

    free(data->codedString);
    _delete_sorted_items(data->items);
    free(data);
}

void _delete_sorted_items(SortedItems *items)
{
    for (register size_t i = 0; i < items->size; ++i)
    {
        //TODO crashes here
        //    free(&(items->items[i]));
    }
    free(items);
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
    return (bits / 8U) + ((bits % 8) ? 1 : 0);
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