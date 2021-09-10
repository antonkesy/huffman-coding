#include "huffman_serialization.h"
#include <stdlib.h>

HuffmanSerializeData *huffman_data_to_serialize_data(HuffmanData *hd) {
    HuffmanSerializeData *serialize_data = malloc(sizeof(HuffmanSerializeData));
    if (serialize_data != NULL && hd != NULL) {
        serialize_data->sort_item_count = *fill_iuint_16(&hd->sort_items->size);
        serialize_data->bits = *fill_iuint_32(&hd->bits);
        serialize_data->sort_items = hd->sort_items->items;
        serialize_data->code = hd->coded_array;
    }
    return serialize_data;
}

HuffmanData *serialize_data_to_huffman_data(HuffmanSerializeData *hsd) {
    HuffmanData *hd = malloc(sizeof(HuffmanData));
    if (hd != NULL && hsd != NULL) {
        hd->sort_items->size = *get_iuint_16_value(&hsd->sort_item_count);
        hd->bits = *get_iuint_32_value(&hsd->bits);
        hd->sort_items->items = hsd->sort_items;
        hd->coded_array = hsd->code;
    }
    return hd;
}


size_t serialize_huffman_data(HuffmanData *hd, unsigned char **dest) {
    //first 2 bytes = sort_items count
    //sizeof size_t
    // sizeof(size_t) = bits of code
    // bytes 1 to sizeof(SortItem) * count = filled with sort_items
    //rest is code
    const size_t bytes_for_coded_string = _fill_bytes_for_bits(hd->bits);
    const size_t total_bytes = _get_huffman_data_needed_bytes_add_coded_string(hd, bytes_for_coded_string);
    unsigned char *output = malloc(total_bytes);
    if (output != NULL) {
        output[0] = (hd->sort_items->size & 0xFF00) >> 8;
        output[1] = hd->sort_items->size & 0xFF;
        output[2] = sizeof(size_t);
        unsigned int offset = 3;

        //bits
        for (unsigned int i = 0; i < sizeof(size_t); ++i) {
            output[i + offset] = ((unsigned char *) (&hd->bits))[i];
        }
        offset += sizeof(size_t);

        //sort sort_items
        for (unsigned int i = 0; i <= hd->sort_items->size * sizeof(SortItem); ++i) {
            output[i + offset] = ((unsigned char *) hd->sort_items->items)[i];
        }
        offset += hd->sort_items->size * sizeof(SortItem);

        //coded string
        for (size_t i = 0U; i < bytes_for_coded_string; ++i) {
            output[i + offset] = hd->coded_array[i];
        }

        *dest = output;
        return total_bytes;
    }
    return 0;
}

HuffmanData *deserialize_huffman_data(const unsigned char *src, size_t *out_byte_read) {
    HuffmanData *ret_data = NULL;
    HuffmanData *hd = malloc(sizeof(HuffmanData));
    if (hd != NULL && src != NULL) {
        const unsigned short items_count = (unsigned short) (src[0] << 8) + src[1];
        const unsigned char size_of_size_t = src[2];
        if (size_of_size_t > sizeof(size_t)) {
            printf("size_t is too small!\n");
        }
        SortItem *items = calloc(1, sizeof(SortItem) * items_count);
        SortedItems *sorted_items = malloc(sizeof(SortedItems));
        if (items != NULL && sorted_items != NULL) {

            size_t offset = 3;
            sorted_items->size = items_count;
            sorted_items->items = items;
            hd->sort_items = sorted_items;

            for (int i = 0; i < size_of_size_t; ++i) {
                ((unsigned char *) (&hd->bits))[i] = src[i + offset];
            }
            offset += size_of_size_t;

            for (unsigned int i = 0; i <= items_count * sizeof(SortItem); ++i) {
                ((unsigned char *) hd->sort_items->items)[i] = src[i + offset];
            }
            offset += items_count * sizeof(SortItem);

            //src is two bytes longer?!
            const size_t coded_array_size = _fill_bytes_for_bits(hd->bits);
            unsigned char *coded_array = malloc(coded_array_size);
            if (coded_array != NULL) {
                hd->coded_array = coded_array;
                for (size_t i = 0U; i < coded_array_size; ++i) {
                    hd->coded_array[i] = src[offset + i];
                }
                *out_byte_read = offset + coded_array_size;
                ret_data = hd;
            }
        }
    }
    return ret_data;
}