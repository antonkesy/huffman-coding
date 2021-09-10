#include <stdlib.h>
#include <string.h>
#include "../../huffman.h"
#include "../../utility/huffman_serialization.h"
#include "../../utility/huffman_utility.h"

int main(void) {
    char *example_string = "BCAADDDCCACACAC";
    HuffmanData *hd = code_into_huffman_data((unsigned char *) example_string, strlen(example_string));
    unsigned char **serialization = (unsigned char **) malloc(sizeof(unsigned char **));
    if (serialization == NULL) {
        return 1;
    }
    serialize_huffman_data(hd, serialization);
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
