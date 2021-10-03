# huffman-coding

Unoptimized huffman coding for files and uint8_t arrays in C

## How it works

### coding
1. Sort uint8_t input array and count frequency of every item
2. Build huffman tree with sorted items using a minheap
3. Generate code for every sorted item
4. Convert input data with huffman code

### decoding
1. Build huffman tree with given huffman data
2. Generate code for every sorted item
3. Convert coded input to uint8_t output array

#### files
If input is a file, the file is cut into buffer size blocks and treated like an uint8_t array.

## Example usage

### code file

```c
huffman_code_file_to_file(INPUT_FILE_NAME, OUTPUT_FILE_NAME, 0);
```

### decode file

```c
huffman_decode_file_to_file(CODED_FILE_NAME, OUTPUT_FILE_NAME);
```

### code uint8_t array

```c
//get uint8_t array of data to convert
uint8_t* example_string = (uint8_t*) "BCAADDDCCACACAC";
//get size of input data
const uint32_t size_string = strlen((char*) example_string);
//create huffman data
HuffmanData* hd = code_into_huffman_data(example_string, size_string);
//need to transfer whole data to decode into original
```

### decode uint8_t array

```c
//create pointer to unsigned char arrays
uint8_t** decoded = (uint8_t**) malloc(sizeof(uint8_t**));
if (decoded != NULL)
{
    //if you need size of the original uint8_t array
    uint32_t output_size;
    //decodes huffman data into original uint8_t input
    decode_huffman_data(hd, decoded, &output_size);
    if (*decoded != NULL)
    {
        //*decoded == original input
    }
    //delete huffman data if done
    delete_huffman_data(hd);
}
```

## Todo & Issues

- big file sometimes not reading/writing correctly causing segment faults
- really unoptimized file read/writes 
- no analysis before choosing block size -> can result in coded file bigger than input
- command line interface not finished

## Disclaimer

This was a semester break project and my first C project (outside of university assignments).
Code is a bit messy and not really optimized or finished ...
Probably not going to visit it soon to rework :)
Here to save some cringe early programmer life/learning projects :)