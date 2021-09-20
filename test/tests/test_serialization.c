#include <stdlib.h>
#include <string.h>
#include "../../huffman.h"
#include "../../utility/huffman_utility.h"
#include "../../utility/huffman_serialization.h"

int main(void) {
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
