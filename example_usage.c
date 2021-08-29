#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"
#include "test/test_utility.h"

#define TEST_INPUT_FILE_NAME "input.txt"
#define TEST_CODED_FILE_NAME "coded.txt"
#define TEST_OUTPUT_FILE_NAME "output.txt"

void create_test_input_file()
{
    FILE *fp;
    fp = fopen(TEST_INPUT_FILE_NAME, "w+");
    if (fp != NULL)
    {
        fprintf(fp, "Hello,\tI'm a testing file :)\n");
        for (register int i = 0; i < 100; ++i)
        {
            fprintf(fp, "number iteration = %i\n", i);
        }
    }
    fclose(fp);
}

void example_usage_files()
{
    create_test_input_file();
    FILE *src = fopen(TEST_INPUT_FILE_NAME, "r");
    if (src == NULL)
    {
        printf("Unable to open file.\n");
        return;
    }

    FILE *codedFile = fopen(TEST_CODED_FILE_NAME, "w");
    if (codedFile == NULL)
    {
        printf("Unable to create file.\n");
        return;
    }

    huffman_code_file_to_file(src, codedFile);

    fclose(src);
    fclose(codedFile);

    codedFile = fopen(TEST_CODED_FILE_NAME, "r");
    if (codedFile == NULL)
    {
        printf("Unable to open file.\n");
        return;
    }

    FILE *dest = fopen(TEST_OUTPUT_FILE_NAME, "w");
    if (dest == NULL)
    {
        printf("Unable to create file.\n");
        return;
    }

    huffman_decode_file_to_file(codedFile, dest);

    printf("files equal ? %i\n", files_equal(codedFile, dest));

    fclose(codedFile);
    fclose(dest);
}

void example_usage()
{
    //get unsigned char array of data to convert
    char *exampleString = "BCAADDDCCACACAC";
    //create huffman data
    HuffmanData *hd = code_into_huffmanData((unsigned char *)exampleString, strlen(exampleString));
    //need to transfer whole data to decode into original

    //create pointer to unsigned char arrays
    unsigned char **decoded = (unsigned char **)malloc(sizeof(unsigned char **));
    //if you need size of the original unsigend char arrays
    size_t outputSize;
    //decodes huffman data into decoded
    decode_huffman_data(hd, decoded, &outputSize);
    printf("%s\n", *decoded);
    //done?
    delete_huffman_data(hd);
}

int main(void)
{
    example_usage();
    return 0;
}