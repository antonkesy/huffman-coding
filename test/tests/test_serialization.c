#include <stdlib.h>
#include <string.h>
#include "../../huffman.h"
#include "../../utility/huffman_utility.h"
#include "../../utility/huffman_serialization.h"
#include "../../utility/huffman_file_to_file.h"

int test_print_serialization()
{
    //check different endian

    //should be
    //0000 0100 0000 0000(sort item size)
    //0000 0100 sizeof(size_t)
    //(0001 1100) (0000 0000) (0000 0000) (0000 0000) bits
    // 4 * SortItems(8) (4x freq) + (1x value)
    //(0000 0001) (0000 0000) (0000 0000) (0000 0000) (0100 0001) (0000 0000) (0000 0000) (0000 0000)
    //(0000 0011) (0000 0000) (0000 0000) (0000 0000) (0100 0010) (0000 0000) (0000 0000) (0000 0000)
    //(0000 0101) (0000 0000) (0000 0000) (0000 0000) (0100 0011) (0000 0000) (0000 0000) (0000 0000)
    //(0000 0110) (0000 0000) (0000 0000) (0000 0000) (0100 0100) (0000 0000) (0000 0000) (0000 0000)
    //coded array = _fill_bytes_for_bits(hd->bits) -> 4
    //(1000 1111) (1011 0110) (1001 1011) (0110 0000)
    char *exampleString = "BCAADDDCCACACAC";
    HuffmanData *hd = code_into_huffman_data((unsigned char *) exampleString, strlen(exampleString));
    unsigned char *serialization_string = NULL;

    uint64_t bytes = 0U;
    serialize_huffman_data(hd, &serialization_string, &bytes);
    if (serialization_string != NULL)
    {
        for (size_t i = 0; i < bytes; ++i)
        {
            print_8bit_as_binary(serialization_string[i]);
            if (i == 0 || i == 1 || i == 5 || i == 13 || ((i > 13) && ((i - 13) % (8) == 0)))
                printf("\n");
        }
        free(serialization_string);
        delete_huffman_data(hd);
    } else
    {
        return 1;
    }
    return 0;
}

int test_de_serialization()
{
    char *example_string = "BCAADDDCCACACAC";
    HuffmanData *hd = code_into_huffman_data((unsigned char *) example_string, strlen(example_string));
    if (hd == NULL)
    {
        return 1;
    }
    unsigned char *serialization = NULL;

    serialize_huffman_data(hd, &serialization, NULL);
    if (serialization == NULL)
    {
        return 1;
    }
    uint64_t bytes_for_data = 0U;
    HuffmanData *hd_de_serial = deserialize_huffman_data(serialization, &bytes_for_data);

    if (hd_de_serial == NULL)
    {
        return 1;
    }

    const int ret_value = !is_huffman_data_equal(hd, hd_de_serial);

    free(serialization);
    serialization = NULL;
    delete_huffman_data(hd);
    hd = NULL;
    delete_huffman_data(hd_de_serial);
    hd_de_serial = NULL;
    return ret_value;
}

int test_mock_big_huffman_data()
{
    uint8_t *random_big_data = malloc(BUFF_SIZE_FILE);
    for (register size_t i = 0U; i < BUFF_SIZE_FILE; ++i)
    {
        random_big_data[i] = i;
    }
    if (random_big_data == NULL)
    { return 1; }
    HuffmanData *hd = code_into_huffman_data(random_big_data, BUFF_SIZE_FILE);
    if (hd == NULL)
    {
        return 1;
    }

    uint8_t *de_serial_string = NULL;

    serialize_huffman_data(hd, &de_serial_string, NULL);
    if (de_serial_string == NULL)
    {
        perror("de_serial_string failed!");
        return 1;
    }
    uint64_t bytes_for_data = 0U;
    HuffmanData *hd_de_serial = deserialize_huffman_data(de_serial_string, &bytes_for_data);
    free(de_serial_string);

    if (hd_de_serial == NULL)
    {
        perror("deserializing failed!");
        return 1;
    }

    uint32_t decoded_string_length = 0U;
    uint8_t *decoded_string = NULL;
    decode_huffman_data(hd_de_serial, &decoded_string, &decoded_string_length);

    if (decoded_string == NULL)
    {
        perror("decode failed!");
        return 1;
    }

    if (decoded_string_length != BUFF_SIZE_FILE)
    {
        perror("data size not equal!");
        return 1;
    }

    if (!uint8_cmp(random_big_data, decoded_string, decoded_string_length))
    {
        perror("coded strings not equal");
        return 1;
    }
    free(random_big_data);
    free(decoded_string);
    if (!is_huffman_data_equal(hd, hd_de_serial))
    {
        perror("huffman data not equal!");
        return 1;
    }
    delete_huffman_data(hd);
    delete_huffman_data(hd_de_serial);
    return 0;
}

int main(void)
{
    return test_print_serialization() || test_de_serialization() || test_mock_big_huffman_data();
}
