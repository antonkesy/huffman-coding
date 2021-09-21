#include <stdint.h>
#include <malloc.h>
#include "huffman_file_to_file.h"
#include "../huffman.h"
#include "huffman_serialization.h"

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