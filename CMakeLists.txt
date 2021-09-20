cmake_minimum_required(VERSION 3.0.0)
project(huffman_coding VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(${CMAKE_CURRENT_SOURCE_DIR}/test/tests/CMakeLists.txt)

if (CMAKE_COMPILER_IS_GNUCC)
    add_compile_options(-std=c11 -Wall -Werror -fsanitize=leak)
endif ()

add_executable(huffman_example example_usage.c huffman.c minheap/minheap.c utility/huffman_utility.c test/test_utility.c utility/huffman_serialization.c utility/huffman_serialization.h utility/independent_int.c utility/independent_int.h utility/huffman_file_to_file.c)
