#include "huffman_serialization.h"
#include <stdlib.h>

HuffmanSerializeData *huffman_data_to_serialize_data(HuffmanData *hd)
{
    HuffmanSerializeData *serialize_data = malloc(sizeof(HuffmanSerializeData));
    if (serialize_data != NULL && hd != NULL)
    {
        serialize_data->sort_item_count = fill_iuint_16(&hd->sort_items->size);
        serialize_data->length = fill_iuint_64(&hd->length);
        serialize_data->sort_items = sort_items_to_serialize_sort_item(hd->sort_items->items, hd->sort_items->size);
        serialize_data->code = hd->coded_array;
        //check if sort items are correct
        if (serialize_data->sort_items != NULL)
        {
            return serialize_data;
        }
    }
    return NULL;
}

HuffmanData *serialize_data_to_huffman_data(HuffmanSerializeData *hsd)
{
    HuffmanData *hd = malloc(sizeof(HuffmanData));
    if (hd != NULL && hsd != NULL)
    {
        SortedItems *sorted_items = malloc(sizeof(SortedItems));
        hd->sort_items = sorted_items;
        if (sorted_items != NULL)
        {
            hd->sort_items->size = get_iuint_16_value((&hsd->sort_item_count));
        }
        hd->length = get_iuint_64_value(&hsd->length);
        hd->coded_array = hsd->code;
        hd->sort_items->items = serialize_sort_items_to_sort_item(hsd->sort_items, hd->sort_items->size);
        if (hd->sort_items->items != NULL)
        {
            return hd;
        }
        _delete_serialize_data(hsd);
    }
    return NULL;
}

SerializeSortItem *sort_items_to_serialize_sort_item(SortItem *sort_items, uint32_t count)
{
    SerializeSortItem *ssi = calloc(count, sizeof(SerializeSortItem));
    if (ssi != NULL)
    {
        for (uint32_t i = 0U; i < count; ++i)
        {
            ssi[i].freq = fill_iuint_64(&(sort_items[i].freq));
            ssi[i].value = sort_items[i].value;
        }
        return ssi;
    }
    return NULL;
}

SortItem *serialize_sort_items_to_sort_item(SerializeSortItem *serialize_sort_item, uint32_t count)
{
    SortItem *si = malloc(sizeof(SortItem) * count);
    if (si != NULL)
    {
        for (uint32_t i = 0U; i < count; ++i)
        {
            si[i].freq = get_iuint_64_value(&(serialize_sort_item[i].freq));
            si[i].value = serialize_sort_item[i].value;
        }
    }
    return si;
}

int serialize_huffman_serialize_data(HuffmanSerializeData *hsd, const uint16_t sort_item_count,
                                     const uint32_t size_coded_string, uint8_t **dest, uint32_t *out_total_bytes)
{
    *dest = malloc(get_huffman_serialize_data_size(sort_item_count, size_coded_string));
    if (*dest != NULL)
    {
        //sort items count
        *((iuint_16_t *) (*dest)) = hsd->sort_item_count;
        unsigned long long offset = sizeof(hsd->sort_item_count);

        //bits
        *((iuint_64_t *) (*dest + offset)) = hsd->length;
        offset += sizeof(hsd->length);

        //sort items
        uint32_t serialize_sort_item_bytes = sort_item_count * sizeof(SerializeSortItem);
        for (int i = 0; i < serialize_sort_item_bytes; ++i)
        {
            (*dest)[offset + i] = ((uint8_t *) (hsd->sort_items))[i];
        }
        offset += serialize_sort_item_bytes;

        //coded string
        for (uint32_t i = 0U; i < size_coded_string; ++i)
        {
            (*dest)[i + offset] = hsd->code[i];
        }

        if (out_total_bytes != NULL)
        {
            *out_total_bytes = offset + size_coded_string;
        }
    }
    return 0;
}

int serialize_huffman_data(HuffmanData *hd, uint8_t **dest, uint32_t *out_total_byte)
{
    uint8_t *output = NULL;
    HuffmanSerializeData *hsd = huffman_data_to_serialize_data(hd);
    if (hsd != NULL)
    {
        serialize_huffman_serialize_data(hsd, hd->sort_items->size, hd->length, &output, out_total_byte);
        _delete_serialize_data(hsd);
    }
    if (dest != NULL)
    {
        *dest = output;
    } else
    {
        free(output);
    }
    return 0;
}

int deserialize_huffman_serialize_data(const uint8_t *src, HuffmanSerializeData **out_hsd, uint32_t *out_total_bytes)
{
    if (src != NULL && out_hsd != NULL)
    {
        *out_hsd = malloc(sizeof(HuffmanSerializeData));
        if (*out_hsd != NULL)
        {
            //sort items count
            (*out_hsd)->sort_item_count = *((iuint_16_t *) src);
            unsigned long long offset = sizeof((*out_hsd)->sort_item_count);

            //bits
            (*out_hsd)->length = *((iuint_64_t *) (src + offset));
            offset += sizeof((*out_hsd)->length);

            //sort items
            uint16_t sort_items_count = get_iuint_16_value(&((*out_hsd)->sort_item_count));
            uint32_t serialize_sort_item_bytes = sort_items_count * sizeof(SerializeSortItem);
            SerializeSortItem *serialize_sort_items = malloc(serialize_sort_item_bytes);
            if (serialize_sort_items != NULL)
            {
                (*out_hsd)->sort_items = serialize_sort_items;
                for (int i = 0; i < serialize_sort_item_bytes; ++i)
                {
                    ((uint8_t *) ((*out_hsd)->sort_items))[i] = src[offset + i];
                }

                offset += serialize_sort_item_bytes;

                //coded string
                uint32_t size_coded_string = get_iuint_64_value(&(*out_hsd)->length);
                uint8_t *coded_array = malloc(size_coded_string);
                if (coded_array != NULL)
                {
                    (*out_hsd)->code = coded_array;
                    for (uint32_t i = 0U; i < size_coded_string; ++i)
                    {
                        (*out_hsd)->code[i] = src[i + offset];
                    }
                }
                *out_total_bytes = offset + size_coded_string;
            }
        }
    }
    return 0;
}

HuffmanData *deserialize_huffman_data(const uint8_t *src, uint32_t *out_byte_read)
{
    HuffmanData *hd = NULL;
    if (src != NULL)
    {
        HuffmanSerializeData **hsd = malloc(sizeof(HuffmanSerializeData *));
        if (hsd != NULL)
        {
            deserialize_huffman_serialize_data(src, hsd, out_byte_read);
            hd = serialize_data_to_huffman_data(*hsd);
            _delete_serialize_data(*hsd);
            free(hsd);
        }
    }
    return hd;
}

size_t get_huffman_serialize_data_size(const uint16_t sort_item_count, const uint32_t size_coded_string)
{
    return sizeof(iuint_16_t) + sizeof(iuint_32_t) + (sizeof(SerializeSortItem) * sort_item_count) + size_coded_string;
}

void _delete_serialize_data(HuffmanSerializeData *hsd)
{
    free(hsd->sort_items);
    free(hsd);
}