cmake_minimum_required(VERSION 3.0.0)
project(huffman_coding VERSION 0.1.0)

if(CMAKE_COMPILER_IS_GNUCC)
    add_compile_options(-Wall -Werror -fsanitize=leak)
endif()
 
add_executable(huffman_test test.c huffman.c minheap/minheap.c minheap/minheaptest.c test_utility.c huffman_utility.c huffman_utility_test.c)

enable_testing()
add_test(huffman_test1 huffman_test)
set_tests_properties(huffman_test1 PROPERTIES WILL_FAIL FALSE)
