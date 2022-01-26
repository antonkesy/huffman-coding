#include "huffman_utility.h"
#include <stdio.h>

void print_huffman_tree(HuffmanTree *tree)
{
    printf("Print tree:\n");
    if (tree->root == NULL)
    {
        printf("tree empty!\n");
    } else
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
        } else
        {
            //value node
            printf("value node %c %u\n", node->value, node->freq);
        }
    }
}

void print_8bit_as_binary(uint8_t c)
{

    size_t flag = 0x80;
    for (register uint8_t i = 0; i < 8; ++i)
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
    for (register uint32_t i = 0; i < hd->length; ++i)
    {
        print_8bit_as_binary(hd->coded_array[i]);
        printf(" ");
    }
}

void print_huffman_node(void *node)
{
    HuffmanNode *huffman_node = (HuffmanNode *) node;
    if (huffman_node->left == NULL && huffman_node->right == NULL)
    {
        printf("Value Node = %i %c\n", huffman_node->freq, huffman_node->value);
    } else
    {
        printf("Parent node = %i\n", huffman_node->freq);
    }
}

bool is_huffman_data_equal(HuffmanData *hd1, HuffmanData *hd2)
{
    //same huffman data
    if (hd1 == hd2)
    {
        return true;
    }

    int ret_value = 1;

    if (hd1->length != hd2->length)
    {
        ret_value = false;
    }
    if (!uint8_cmp(hd1->coded_array, hd2->coded_array, hd1->length))
    {
        ret_value = false;
    }
    if (!is_sorted_items_equal(hd1->sort_items, hd2->sort_items))
    {
        ret_value = false;
    }

    return ret_value;
}

bool uint8_cmp(const uint8_t *string_1, const uint8_t *string_2, uint32_t size)
{
    if (string_1 == NULL || string_2 == NULL)
    { return false; }
    for (uint32_t i = 0U; i < size; ++i)
    {
        if (string_1[i] != string_2[i])
        {
            return false;
        }
    }
    return true;
}

bool is_sorted_items_equal(SortedItems *items1, SortedItems *items2)
{
    if (items1 == items2)
    {
        return true;
    }

    if (items1->size != items2->size)
    {
        return false;
    }

    for (uint16_t i = 0; i < items1->size; ++i)
    {
        if (!is_sort_item_equal(&(items1->items[i]), &(items2->items[i])))
        {
            return false;
        }
    }

    return 1;
}

bool is_sort_item_equal(SortItem *item1, SortItem *item2)
{
    return (item1->freq == item2->freq) && (item1->value == item2->value);
}
