cmake_minimum_required(VERSION 3.0.0)
project(huffman_coding VERSION 0.1.0
        DESCRIPTION "basic compression coding library using simple huffman coding for C++"
        HOMEPAGE_URL "https://github.com/antonkesy/huffman-coding"
        )

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HUFFMAN_SRC
        src/huffman_coder.cpp
        src/huffman_coding.cpp
        src/sorted_chars/sorted_chars.cpp
        src/sorted_chars/huffman_tree/huffman_tree.cpp
        )

add_library(huffman_coding STATIC ${HUFFMAN_SRC})
add_library(huffman_coding_shared SHARED ${HUFFMAN_SRC})

add_executable(example example_usage.cpp)
target_link_libraries(example PRIVATE huffman_coding)

add_subdirectory(test)