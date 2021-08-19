cmake_minimum_required(VERSION 3.0.0)
project(HuffmanCode VERSION 0.1.0)

include(CTest)

if(BUILD_TESTING)
add_executable(HuffmanCode Test.c huffman.c priorityqueue/priorityqueue.c priorityqueue/priorityqueuetest.c)
endif()

