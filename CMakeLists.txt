cmake_minimum_required(VERSION 3.0.0)
project(huffman_coding VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(test/tests)

set(huffman_essentials
        huffman.c
        minheap/minheap.c
        )

set(utility
        utility/huffman_serialization.c
        utility/huffman_serialization.h
        utility/independent_int.c
        utility/independent_int.h
        utility/huffman_file_to_file.c
        utility/memory_space.c
        utility/huffman_utility.c
        )

add_library(huffman_coding STATIC ${huffman_essentials} ${utility})