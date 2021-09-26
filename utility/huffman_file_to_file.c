#include <stdint.h>
#include <malloc.h>
#include "huffman_file_to_file.h"
#include "../huffman.h"
#include "huffman_serialization.h"

void huffman_code_file_to_file(const char *src_file_name, const char *des_coded_file_name)
{
    //open src file
    FILE *src_file = open_file_to_read(src_file_name);
    if (is_file_open_correctly(src_file))
    {
        perror("Unable to open src file!");
    }

    //open des file
    FILE *coded_file = open_file_to_write(des_coded_file_name);
    if (is_file_open_correctly(coded_file))
    {
        perror("Unable to create file.\n");
    }

    _huffman_code_file_to_file(src_file, coded_file);

    fclose(src_file);
    fclose(coded_file);
}

void huffman_decode_file_to_file(const char *src_coded_file_name, const char *des_file_name)
{
    FILE *coded_file = open_file_to_read(src_coded_file_name);
    if (is_file_open_correctly(coded_file))
    {
        perror("Unable to open file.\n");
    }

    FILE *dest = open_file_to_write(des_file_name);
    if (is_file_open_correctly(dest))
    {
        perror("Unable to create file.\n");
    }

    _huffman_decode_file_to_file(coded_file, dest);

    fclose(coded_file);
    fclose(dest);
}

void _huffman_code_file_to_file(FILE *src, FILE *des)
{
    uint8_t *buffer = malloc(BUFF_SIZE_FILE);
    if (buffer != NULL)
    {
        uint32_t elements_read;
        do
        {
            elements_read = fread(buffer, 1, BUFF_SIZE_FILE, src);
            HuffmanData *hd = code_into_huffman_data(buffer, elements_read);
            uint8_t *bytes_to_write = NULL;
            uint32_t amount_write_bytes = 0U;
            serialize_huffman_data(hd, &bytes_to_write, &amount_write_bytes);
            fwrite(bytes_to_write, 1, amount_write_bytes, des);
            delete_huffman_data(hd);
        }
        while (elements_read == BUFF_SIZE_FILE);
        printf("write done\n");
        free(buffer);
    }
}

void _huffman_decode_file_to_file(FILE *src, FILE *des)
{
    uint8_t *buffer = malloc(BUFF_SIZE_FILE);
    if (buffer != NULL)
    {
        long read_offset = 0U;
        uint32_t elements_read;
        uint32_t byte_needed_for_data = 0U;

        do
        {
            if (fseek(src, -read_offset, SEEK_CUR) != 0)
            {
                perror("decode fseek erro\n");
            }
            elements_read = fread(buffer, 1, BUFF_SIZE_FILE, src);
            if (elements_read == 0 || ferror(src))
            {
                break;
            }
            HuffmanData *hd = deserialize_huffman_data(buffer, &byte_needed_for_data);
            uint8_t **decoded = malloc(sizeof(uint8_t **));
            if (decoded != NULL)
            {
                uint32_t output_size = 0U;
                decode_huffman_data(hd, decoded, &output_size);
                if (*decoded != NULL)
                {
                    fwrite(*decoded, 1, output_size, des);
                }
            }
            free(decoded);
            delete_huffman_data(hd);
            //TODO move file pointer by subtracting read and needed and go back from current position
            read_offset = (long) (elements_read - byte_needed_for_data);
        }
        while (elements_read > byte_needed_for_data);
        printf("read done\n");
        free(buffer);
    }
}

FILE *open_file_to_write(const char *file_name)
{
    return fopen(file_name, "wb");
}

FILE *open_file_to_read(const char *file_name)
{
    return fopen(file_name, "rb");
}

bool is_file_open_correctly(FILE *file)
{
    return (file != NULL && ferror(file));
}