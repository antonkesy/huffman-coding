project(huffman_test)
cmake_minimum_required(VERSION 2.8.12)

add_executable(huffman_test test/test.c huffman.c minheap/minheap.c utility/huffman_utility.c test/test_utility.c)
add_executable(test_serialization test/test_serialization.c huffman.c minheap/minheap.c utility/huffman_utility.c test/test_utility.c)

enable_testing()
add_test(complete_test huffman_test)
set_tests_properties(complete_test PROPERTIES WILL_FAIL FALSE)


enable_testing()
add_test(serial_test test_serialization)
set_tests_properties(serial_test PROPERTIES WILL_FAIL FALSE)