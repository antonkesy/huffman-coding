cmake_minimum_required(VERSION 3.0.0)
project(huffman_coding VERSION 0.1.0)

include(${CMAKE_CURRENT_SOURCE_DIR}/test/CMakeLists.txt)

if(CMAKE_COMPILER_IS_GNUCC)
    add_compile_options(-Wall -Werror -fsanitize=leak)
endif()

add_executable(huffman_example example_usage.c huffman.c minheap/minheap.c utility/huffman_utility.c test/test_utility.c)
