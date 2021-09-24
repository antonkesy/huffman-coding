#include <stdlib.h>
#include <string.h>
#include "../../huffman.h"
#include "../../utility/huffman_utility.h"
#include "../../utility/huffman_serialization.h"

int test_print_serialization() {
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
    unsigned char **serialization = (unsigned char **) malloc(sizeof(unsigned char **));
    if (serialization != NULL) {
        size_t bytes = 0U;
        serialize_huffman_data(hd, serialization, &bytes);
        if (*serialization != NULL) {
            for (size_t i = 0; i < bytes; ++i) {
                print_8bit_as_binary((*serialization)[i]);
                if (i == 0 || i == 1 || i == 5 || i == 13 || ((i > 13) && ((i - 13) % (8) == 0)))
                    printf("\n");
            }
        } else {
            return 1;
        }
    } else {
        return 1;
    }
    return 0;
}

int test_de_serialization() {
    char *example_string = "BCAADDDCCACACAC";
    HuffmanData *hd = code_into_huffman_data((unsigned char *) example_string, strlen(example_string));
    unsigned char **serialization = (unsigned char **) malloc(sizeof(unsigned char **));
    if (serialization == NULL) {
        return 1;
    }
    serialize_huffman_data(hd, serialization, NULL);
    if (*serialization == NULL) {
        return 1;
    }
    size_t bytes_for_data = 0U;
    HuffmanData *hd_de_serial = deserialize_huffman_data(*serialization, &bytes_for_data);

    if (hd_de_serial == NULL) {
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

int main(void) {
    return test_print_serialization() || test_de_serialization();
}
