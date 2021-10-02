#include <stdint.h>
#include <malloc.h>
#include "huffman_file_to_file.h"
#include "../huffman.h"
#include "huffman_serialization.h"

void huffman_code_file_to_file(const char *src_file_name, const char *des_coded_file_name, long buffer_size)
{
    //open src file
    FILE *src_file = open_file_to_read(src_file_name);
    if (is_file_open_correctly(src_file))
    {
        perror("Unable to open src file!");
        return;
    }

    //open des file
    FILE *coded_file = open_file_to_write(des_coded_file_name);
    if (is_file_open_correctly(coded_file))
    {
        perror("Unable to create file.\n");
        return;
    }

    _huffman_code_file_to_file(src_file, coded_file, buffer_size);

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

void _huffman_code_file_to_file(FILE *src, FILE *des, long buffer_size)
{
    if (src == NULL || des == NULL)
    {
        perror("file pointer null");
        return;
    }
    uint8_t *buffer = malloc(buffer_size);

    if (buffer != NULL)
    {
        set_placeholder_buffer_size_header(des);
        uint64_t max_buffer_size = 0U;
        uint64_t elements_read;
        HuffmanData *hd = NULL;
        do
        {
            elements_read = fread(buffer, 1, buffer_size, src);
            hd = code_into_huffman_data(buffer, elements_read);
            if (hd == NULL)
            {
                perror("file to file code into huffman data failed!");
                break;
            }
            uint64_t amount_write_bytes = 0U;
            uint8_t *bytes_to_write = NULL;
            serialize_huffman_data(hd, &bytes_to_write, &amount_write_bytes);
            if (bytes_to_write != NULL && amount_write_bytes > 0U)
            {
                fwrite(bytes_to_write, 1, amount_write_bytes, des);
                free(bytes_to_write);
                if (amount_write_bytes > max_buffer_size)
                {
                    max_buffer_size = amount_write_bytes;
                }
            }
            delete_huffman_data(hd);
        }
        while (elements_read == buffer_size);
        set_buffer_size_header(max_buffer_size, des);
        printf("write done\n");
        free(buffer);
    }
}

void _huffman_decode_file_to_file(FILE *src, FILE *des)
{
    if (src == NULL || des == NULL)
    {
        perror("file pointer null");
        return;
    }
    uint64_t min_buffer_size = get_buffer_size_from_header(src);
    uint8_t *buffer = malloc(min_buffer_size);
    if (buffer != NULL)
    {
        int64_t read_offset = 0U;
        uint64_t elements_read;
        uint64_t byte_needed_for_data = 0U;

        do
        {
            if (fseek64(src, -read_offset, SEEK_CUR) != 0)
            {
                perror("decode fseek error");
                break;
            }
            elements_read = fread(buffer, 1, min_buffer_size, src);
            if (elements_read == 0 || ferror(src))
            {
                break;
            }
            HuffmanData *hd = deserialize_huffman_data(buffer, &byte_needed_for_data);
            if (hd != NULL)
            {
                uint8_t **decoded = malloc(sizeof(uint8_t **));
                if (decoded != NULL)
                {
                    uint32_t output_size = 0U;
                    decode_huffman_data(hd, decoded, &output_size);
                    if (*decoded != NULL)
                    {
                        fwrite(*decoded, 1, output_size, des);
                        free(*decoded);
                    }
                    free(decoded);
                }
                delete_huffman_data(hd);
            }
            read_offset = (long) (elements_read - byte_needed_for_data);
        }
        while (elements_read >= byte_needed_for_data);
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

uint64_t get_buffer_size_from_header(FILE *pFile)
{
    fseek(pFile, 0, SEEK_SET);
    iuint_64_t buffer_size_header;
    fread(&buffer_size_header, sizeof(iuint_64_t), 1, pFile);
    return get_iuint_64_value(&buffer_size_header);
}

void set_buffer_size_header(uint64_t buffer_size, FILE *pFile)
{
    fseek(pFile, 0, SEEK_SET);
    iuint_64_t i_buffer_size = fill_iuint_64(&buffer_size);
    fwrite(&i_buffer_size, sizeof(iuint_64_t), 1, pFile);
}

void set_placeholder_buffer_size_header(FILE *pFile)
{
    uint64_t placeholder_value = 0U;
    fwrite(&placeholder_value, sizeof(uint64_t), 1, pFile);
}

uint64_t fseek64(FILE *pFile, int64_t offset, int origin)
{
    uint64_t positions_moved = 0U;
    if (pFile != NULL && (origin == SEEK_SET || origin == SEEK_CUR || origin == SEEK_END))
    {
        long long_offset;

        while (offset != 0U)
        {
            long_offset = (long) offset;
            offset -= long_offset;
            fseek(pFile, long_offset, origin);
        }
    }

    return positions_moved;
}