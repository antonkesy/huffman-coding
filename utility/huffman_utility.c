#include "huffman_utility.h"

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
        print_char_as_binary(hd->coded_array[i]);
        printf(" ");
    }
}

void print_huffman_node(void *node)
{
    HuffmanNode *huffman_node = (HuffmanNode *)node;
    if (huffman_node->left == NULL && huffman_node->right == NULL)
    {
        printf("Value Node = %i %c\n", huffman_node->freq, huffman_node->value);
    }
    else
    {
        printf("Parent node = %i\n", huffman_node->freq);
    }
}

int is_huffman_data_equal(HuffmanData *hd1, HuffmanData *hd2)
{
    //same huffman data
    if (hd1 == hd2)
    {
        return 1;
    }

    int ret_value = 1;

    if (hd1->bits != hd2->bits)
    {
        printf("huffman data bits not same!\n");
        ret_value = 0;
    }
    if (!is_coded_string_equal(hd1->coded_array, hd2->coded_array, _fill_bytes_for_bits(hd1->bits)))
    {
        printf("huffman data coded string not same!\n");
        ret_value = 0;
    }
    if (!is_sorted_items_equal(hd1->sort_items, hd2->sort_items))
    {
        printf("huffman data sorted items not same!\n");
        ret_value = 0;
    }

    return ret_value;
}

int is_coded_string_equal(unsigned char *coded_string_1, unsigned char *coded_string_2, size_t size)
{
    for (size_t i = 1U; i < size; ++i)
    {
        if (coded_string_1[i] != coded_string_2[i])
        {
            unsigned char c1 = coded_string_1[i];
            unsigned char c2 = coded_string_2[i];
            printf("coded char at pos %i not same! %c %c", i, c1, c2);
            return 0;
        }
    }
    return 1;
}

int is_sorted_items_equal(SortedItems *items1, SortedItems *items2)
{
    if (items1 == items2)
    {
        return 1;
    }

    if (items1->size != items2->size)
    {
        return 0;
    }

    for (register short int i = 0; i < items1->size; ++i)
    {
        if (!is_sort_item_equal(&(items1->items[i]), &(items2->items[i])))
        {
            return 0;
        }
    }

    return 1;
}

int is_sort_item_equal(SortItem *item1, SortItem *item2)
{
    return (item1->freq == item2->freq) && (item1->value == item2->value);
}
