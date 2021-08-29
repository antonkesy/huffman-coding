project(huffman_test)
cmake_minimum_required(VERSION 2.8.12)

add_executable(test_test test/test.c huffman.c minheap/minheap.c utility/huffman_utility.c test/test_utility.c)

enable_testing()
add_test(complete_test test_test) 
set_tests_properties(complete_test PROPERTIES WILL_FAIL FALSE)