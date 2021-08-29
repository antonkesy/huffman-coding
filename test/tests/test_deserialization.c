#include <stdlib.h>
#include <string.h>
#include "../../huffman.h"

int main(void)
{
    char *exampleString = "BCAADDDCCACACAC";
    HuffmanData *hd = code_into_huffmanData((unsigned char *)exampleString, strlen(exampleString));
    unsigned char **serialization = (unsigned char **)malloc(sizeof(unsigned char **));
    serialize_huffmandata(hd, serialization);
    size_t bytes_for_data = 0U;
    HuffmanData *hdDeSeri = deserialize_huffmandata(*serialization, &bytes_for_data);

    if (hd->bits != hdDeSeri->bits)
    {
        printf("bits not same!\n");
        return 1;
    }
    for (int i = 0; i < hd->sort_items->size; ++i)
    {
        printf("%i %i\n", hd->sort_items->items[i].freq, hd->sort_items->items[i].value);
        if (hd->sort_items->items[i].freq != hd->sort_items->items[i].value)
        {
            //not same value!
            return 1;
        }
    }

    free(serialization);
    serialization = NULL;
    delete_huffman_data(hd);
    hd = NULL;
    delete_huffman_data(hdDeSeri);
    hdDeSeri = NULL;
    return 0;
}