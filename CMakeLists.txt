cmake_minimum_required(VERSION 3.0.0)
project(HuffmanCode VERSION 0.1.0)

include(CTest)

if(CMAKE_COMPILER_IS_GNUCC)
    add_compile_options(-Wall -Werror -fsanitize=leak)
endif()
 
add_executable(HuffmanCode Test.c huffman.c minheap/minheap.c minheap/minheaptest.c test_utility.c)


