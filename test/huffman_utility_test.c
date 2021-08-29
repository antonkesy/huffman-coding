#include <stdio.h>
#include <stdlib.h>
#include "../huffman.h"
#include "../utility/huffman_utility.h"

int test_equal_sort_item()
{
    SortItem sa = {3, 'a'};
    SortItem sb = {5, 'a'};
    SortItem sc = {3, 'b'};
    SortItem sa1 = {3, 'a'};
    printf("%i %i %i", is_sort_item_equal(&sa, &sa1), is_sort_item_equal(&sa, &sb), is_sort_item_equal(&sa, &sc));
    return 0;
}

int test_equal_sorted_items()
{
    SortItem *items1 = (SortItem *)malloc(sizeof(SortItem) * 3);
    SortItem *items2 = (SortItem *)malloc(sizeof(SortItem) * 3);
    for (int i = 0; i < 3; ++i)
    {
        items1[i].freq = i;
        items1[i].value = i;
        items2[i].freq = i + 1;
        items2[i].value = i + 1;
    }
    SortedItems si1 = {3, items1};
    SortedItems si2 = {3, items2};
    SortedItems si3 = {5, items1};
    SortedItems si11 = {3, items1};
    printf("%i %i %i", is_sorted_items_equal(&si1, &si11), is_sorted_items_equal(&si1, &si2), is_sorted_items_equal(&si1, &si3));
    return 0;
}

int test_is_huffman_data_equal()
{

    SortItem *items1 = (SortItem *)malloc(sizeof(SortItem) * 3);
    SortItem *items2 = (SortItem *)malloc(sizeof(SortItem) * 3);
    for (int i = 0; i < 3; ++i)
    {
        items1[i].freq = i;
        items1[i].value = i;
        items2[i].freq = i + 1;
        items2[i].value = i + 1;
    }
    SortedItems si1 = {3, items1};
    SortedItems si2 = {3, items2};

    unsigned char *ca1 = (unsigned char *)"one";
    unsigned char *ca2 = (unsigned char *)"two";

    HuffmanData h1 = {3, ca1, &si1};
    HuffmanData h11 = {3, ca1, &si1};
    HuffmanData h2 = {1, ca1, &si1};
    HuffmanData h3 = {3, ca2, &si1};
    HuffmanData h4 = {3, ca1, &si2};

    printf("%i %i %i %i", is_huffman_data_equal(&h1, &h11), is_huffman_data_equal(&h1, &h2), is_huffman_data_equal(&h1, &h3), is_huffman_data_equal(&h1, &h4));

    return 0;
}

int test_coded_string_equal()
{
    unsigned char *coded_string_1 = (unsigned char *)"hello";
    unsigned char *coded_string_1_1 = (unsigned char *)"hello";
    unsigned char *coded_string_2 = (unsigned char *)"hello!";
    unsigned char *coded_string_3 = (unsigned char *)":) i bims 1 test";

    printf("%i %i %i", is_coded_string_equal(coded_string_1, coded_string_1_1, 5), is_coded_string_equal(coded_string_1, coded_string_2, 5), is_coded_string_equal(coded_string_1, coded_string_3, 5));
    return 0;
}