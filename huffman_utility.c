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
    return 0;
}