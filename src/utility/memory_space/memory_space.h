#ifndef HUFFMAN_MEMORY_SPACE_H
#define HUFFMAN_MEMORY_SPACE_H

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    uint64_t bytes;
    uint8_t rest_bits;
} MemorySpace;

void add_bits_memory_space(MemorySpace *ms, uint64_t bits);

void sub_bits(MemorySpace *ms, uint64_t bits);

bool is_empty_memory_space(MemorySpace *ms);

uint64_t get_fill_bytes(MemorySpace *ms);

#endif //HUFFMAN_MEMORY_SPACE_H
