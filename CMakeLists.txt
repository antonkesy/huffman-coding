cmake_minimum_required(VERSION 3.0.0)
project(huffman_coding VERSION 0.1.0
        DESCRIPTION "basic compression coding library using simple huffman coding for c/cpp"
        HOMEPAGE_URL "https://github.com/antonkesy/huffman-coding"
        )

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

enable_testing()
add_subdirectory(test/tests)

set(huffman_essentials
        src/huffman.c
        src/minheap/minheap.c
        )

set(utility
        src/utility/huffman_serialization.c
        src/utility/independent_int.c
        src/utility/huffman_file_to_file.c
        src/utility/memory_space.c
        src/utility/huffman_utility.c
        )

add_library(huffman_coding STATIC ${huffman_essentials} ${utility})
add_library(huffman_coding_shared SHARED ${huffman_essentials} ${utility})

add_executable(example example_usage.c test/test_utility.c)
target_link_libraries(example PRIVATE huffman_coding)
