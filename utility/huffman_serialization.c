#include "huffman_serialization.h"
#include <stdlib.h>

HuffmanSerializeData *huffman_data_to_serialize_data(HuffmanData *hd) {
    HuffmanSerializeData *serialize_data = malloc(sizeof(HuffmanSerializeData));
    if (serialize_data != NULL && hd != NULL) {
        serialize_data->sort_item_count = *fill_iuint_16(&hd->sort_items->size);
        serialize_data->bits = *fill_iuint_32(&hd->bits);
        serialize_data->sort_items = sort_items_to_serialize_sort_item(hd->sort_items->items, hd->sort_items->size);
        serialize_data->code = hd->coded_array;
    }
    return serialize_data;
}

HuffmanData *serialize_data_to_huffman_data(HuffmanSerializeData *hsd) {
    HuffmanData *hd = malloc(sizeof(HuffmanData));
    if (hd != NULL && hsd != NULL) {
        SortedItems *sorted_items = malloc(sizeof(SortedItems));
        hd->sort_items = sorted_items;
        if (sorted_items != NULL) {
            hd->sort_items->size = *get_iuint_16_value((&hsd->sort_item_count));
        }
        hd->bits = *get_iuint_32_value(&hsd->bits);
        SortItem *sort_items = malloc(hd->sort_items->size);
        if (sort_items != NULL) {
            hd->sort_items->items = sort_items;
            hd->sort_items->items = serialize_sort_items_to_sort_item(hsd->sort_items, hd->sort_items->size);
        }
        hd->coded_array = hsd->code;
    }
    return hd;
}

SerializeSortItem *sort_items_to_serialize_sort_item(SortItem *sort_items, uint32_t count) {
    SerializeSortItem *ssi = malloc(sizeof(SerializeSortItem) * count);
    if (ssi != NULL) {
        for (uint32_t i = 0U; i < count; ++i) {
            ssi[i].freq = *fill_iuint_64(&(sort_items[i].freq));
            ssi[i].value = sort_items[i].value;
        }
    }
    return ssi;
}

SortItem *serialize_sort_items_to_sort_item(SerializeSortItem *serialize_sort_item, uint32_t count) {
    SortItem *si = malloc(sizeof(SortItem) * count);
    if (si != NULL) {
        for (uint32_t i = 0U; i < count; ++i) {
            si[i].freq = *get_iuint_64_value(&(serialize_sort_item[i].freq));
            si[i].value = serialize_sort_item[i].value;
        }
    }
    return si;
}

int
serialize_huffman_serialize_data(HuffmanSerializeData *hsd, const uint16_t sort_item_count,
                                 const uint32_t size_coded_string, uint8_t *dest) {
    if (dest != NULL) {
        //sort items count
        for (int i = 0; i < SORT_ITEM_SIZE_OF; ++i) {
            dest[i] = hsd->sort_item_count.bytes[i];
        }
        unsigned long long offset = SORT_ITEM_SIZE_OF;

        //bits
        for (int i = 0; i < BITS_SIZE_OF; ++i) {
            dest[offset + i] = hsd->bits.bytes[i];
        }
        offset += BITS_SIZE_OF;

        //sort items
        uint32_t serialize_sort_item_bytes = sort_item_count * sizeof(SerializeSortItem);
        for (int i = 0; i < serialize_sort_item_bytes; ++i) {
            dest[offset + i] = ((uint8_t * )(hsd->sort_items))[i];
        }
        offset += serialize_sort_item_bytes;

        //coded string
        for (uint32_t i = 0U; i < size_coded_string; ++i) {
            dest[i + offset] = hsd->code[i];
        }
    }
    return 0;
}

int serialize_huffman_data(HuffmanData *hd, uint8_t **dest, uint32_t *out_total_byte) {
    const uint32_t bytes_for_coded_string = _fill_bytes_for_bits(hd->bits);
    const uint32_t total_bytes = _get_huffman_data_needed_bytes_add_coded_string(hd, bytes_for_coded_string);
    if (out_total_byte != NULL) {
        *out_total_byte = total_bytes;
    }
    uint8_t *output = malloc(total_bytes);
    if (output != NULL) {
        serialize_huffman_serialize_data(huffman_data_to_serialize_data(hd), hd->sort_items->size,
                                         bytes_for_coded_string, output);
        if (dest != NULL) {
            *dest = output;
        }
    }
    return 0;
}

int deserialize_huffman_serialize_data(const uint8_t *src, HuffmanSerializeData **out_hsd, uint32_t *out_total_bytes) {
    if (src != NULL && out_hsd != NULL) {
        *out_hsd = malloc(sizeof(HuffmanSerializeData));
        if (*out_hsd != NULL) {
            //sort items count
            for (int i = 0; i < SORT_ITEM_SIZE_OF; ++i) {
                (*out_hsd)->sort_item_count.bytes[i] = src[i];
            }
            unsigned long long offset = SORT_ITEM_SIZE_OF;

            //bits
            for (int i = 0; i < BITS_SIZE_OF; ++i) {
                (*out_hsd)->bits.bytes[i] = src[offset + i];
            }
            offset += BITS_SIZE_OF;

            //sort items
            //FIXME sort_items_count not correctly read
            uint16_t sort_items_count = *get_iuint_16_value(&((*out_hsd)->sort_item_count));
            uint32_t serialize_sort_item_bytes = sort_items_count * sizeof(SerializeSortItem);
            SerializeSortItem *serialize_sort_items = malloc(serialize_sort_item_bytes);
            if (serialize_sort_items != NULL) {
                (*out_hsd)->sort_items = serialize_sort_items;
                for (int i = 0; i < serialize_sort_item_bytes; ++i) {
                    ((uint8_t * )((*out_hsd)->sort_items))[i] = src[offset + i];
                }

                offset += serialize_sort_item_bytes;

                //coded string
                uint32_t size_coded_string = _fill_bytes_for_bits(*get_iuint_32_value(&(*out_hsd)->bits));
                uint8_t *coded_array = malloc(size_coded_string);
                if (coded_array != NULL) {
                    (*out_hsd)->code = coded_array;
                    for (uint32_t i = 0U; i < size_coded_string; ++i) {
                        (*out_hsd)->code[i] = src[i + offset];
                    }
                }
                *out_total_bytes = offset + size_coded_string;
            }
        }
    }
    return 0;
}

HuffmanData *deserialize_huffman_data(const uint8_t *src, uint32_t *out_byte_read) {
    HuffmanData *ret_data = NULL;
    if (src != NULL) {
        HuffmanSerializeData **hsd = malloc(sizeof(HuffmanSerializeData *));
        deserialize_huffman_serialize_data(src, hsd, out_byte_read);
        ret_data = serialize_data_to_huffman_data(*hsd);
    }
    return ret_data;
}